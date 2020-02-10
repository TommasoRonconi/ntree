// ===============================================================

template< const size_t dim, const size_t depth >
ntree< dim, depth >::ntree ( const std::vector< double > & coords,
			     const double & boxmin,
			     const double & boxmax ) :
  _boxmin{ boxmin }, _boxmax{ boxmax },
  _lenght{ ( boxmax - boxmin ) / ( 1 << depth ) },
  _expand{ 1. / _lenght }, _size{ coords.size() / dim }
{

  // some preliminary checks on dimensions of the input coordinates vector
  if ( _size > dim * ( 1 << depth ) )
    throw sico_err::size_invalid( "The provided vector of coordinates is too big ( size = " +
				  std::to_string( coords.size() ) +
				  " > " + std::to_string( dim * ( 1 << depth ) ) +
				  ") for your choice of the template parameters." );
  if ( coords.size() % dim > 0 )
    throw sico_err::size_invalid( "The provided vector of coordinates is not " +
				  std::to_string( dim ) + "-dimensional!" );

  // allocate vector of pointers to n-dimensional particle:
  std::vector< nparticle< dim, depth > * > bucket ( _size );

  // consider off-set to center the hilbert grid:
  double locmin = boxmin + 0.5 * _lenght;

  // for ( auto && _c : coords )
  //   std::cout << _c << "\t";
  // std::cout << "\n";

  // this fills the bucket with n-dimensional particles:
  // ( multi-threading friendly )
#pragma omp parallel for
  for ( size_t ii = 0; ii < _size; ++ii ) {
    
    // convert coords (floating point) to hilbert positions (hilbert_coord_t)
    hilbert_coord_t< dim, depth > hpos;
    for ( size_t jj = 0; jj < dim; ++jj )
      hpos[ jj ] = std::size_t( ( coords[ ii * dim + jj ] - locmin ) * _expand );

    // insert new particle in bucket by getting key on the fly:
    bucket[ ii ] = new nparticle< dim, depth > { hpos, { coords.begin() + ( ii * dim),
							 coords.begin() + ( ii * dim) + dim },
						 _hc.get_key( _hc.get_grid( hpos ) ).to_ulong() };
    
  } // back to serial.

  // sort the n-dimensional particle array:
  std::sort( bucket.begin(), bucket.end(),
  	     [&]( sico::utl::nparticle< dim, depth > * a,
  		  sico::utl::nparticle< dim, depth > * b ){
  	       return a->h_key < b->h_key;
  	     } );
  // for ( auto && _b : bucket ) 
  //   std::cout << _b->h_key << "\t";
  // std::cout << "\n";

  // reset root from nullptr to level0 n-dim cell
  root.reset( new ncell< dim, depth > {} );
  
  // call recursive insert:
  root->insert( bucket );

}

// ===============================================================

template< const size_t dim, const size_t depth >
std::vector< size_t > ntree< dim, depth >::_keys_from_perm ( const std::vector< std::size_t > & arr,
							     const size_t lenght ) {

  std::vector< size_t > keys;
  keys.reserve( sico::utl::ipow( lenght, dim ) );
  hilbert_coord_t< dim, depth > hpos;
    
  // to keep track of next element in each of 
  // the n arrays
  int* indices = new int[ dim ]; 
  
  // initialize with first element's index 
  for ( size_t ii = 0; ii < dim; ++ii ) indices[ ii ] = 0;

  while ( 1 ) { 
  
    // get key from current combination 
    for ( size_t ii = 0; ii < dim; ++ii ) {
      hpos[ ii ] = arr[ ii * lenght + indices[ ii ] ];
      // std::cout << hpos( ii ) << " ";
    }
    // std::cout << std::endl; 
    keys.push_back( _hc.get_key( _hc.get_grid( hpos ) ).to_ulong() );
  
    // find the rightmost array that has more 
    // elements left after the current element  
    // in that array 
    int next = dim - 1; 
    while ( next >= 0 && ( indices[ next ] + 1 >= lenght ) ) --next;
	
    // no such array is found so no more  
    // combinations left 
    if ( next < 0 ) {
      delete[] indices;
      return keys;
    }
  
    // if found move to next element in that  
    // array 
    ++indices[ next ]; 
  
    // for all arrays to the right of this  
    // array current index again points to  
    // first element 
    for ( size_t ii = next + 1; ii < dim; ++ii ) indices[ ii ] = 0;
    
  }
  
  delete[] indices;
  return keys;
  
}
  
// ===============================================================

template< const size_t dim, const size_t depth >
std::vector< size_t > ntree< dim, depth >::find ( const std::vector< double > & coords,
						  const double rad ) {

  // find number of cells per dimension:
  int nrad = std::round( rad * _expand );

  // maximum index allows for cycling (periodic boundaries)
  size_t idx_max = ( 1 << depth );

  // allocate vector for index ranges in dim dimensions:
  std::vector< std::size_t > idx_ranges ( dim * ( 2 * nrad + 1 ) );

  // find range of indexes in each dimension
  for ( size_t jj = 0; jj < dim; ++jj ) {

    // find position from float coords:    
    int pos = int( ( coords[ jj ] - _boxmin ) * _expand );
    
    // std::cout << pos << ":\t";
    for ( int ii = pos - nrad; ii <= pos + nrad; ++ii ) // {
      idx_ranges[ jj * ( 2 * nrad + 1 ) + ii - pos + nrad ] = ( ii + idx_max ) % idx_max;
    //   std::cout
    // 	<< "\t( " << jj * ( 2 * nrad + 1 ) + ii - pos + nrad
    // 	<< " ): " << idx_ranges[ jj * ( 2 * nrad + 1 ) + ii - pos + nrad ];
    // }
    // std::cout << "\n";
  }

  // find vector of neighbouring keys:
  auto keys = _keys_from_perm( idx_ranges, 2 * nrad + 1 );

  // erase from vector keys not present in tree:
  auto _k = keys.begin();
  while ( _k != keys.end() ) 
    if ( *find( *_k ) ) ++_k; // if key exists, increase iterator
    else _k = keys.erase( _k ); // if key does not exist, erase and reset iterator

  return keys;
  
}

// ===============================================================
