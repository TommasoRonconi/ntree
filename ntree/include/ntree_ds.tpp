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

  // reset root from nullptr to level0 n-dim cell
  root.reset( new ncell< dim, depth > {} );
  
  // call recursive insert:
  root->insert( bucket );

  // set cell-limits recursively
  root->set_limits( 0, _hc );

}

// ===============================================================

template< const size_t dim, const size_t depth >
std::vector< std::size_t > ntree< dim, depth >::find ( const std::vector< double > & coords,
						       const double rad ) {

  // find number of cells per dimension:
  int nrad = std::round( rad * _expand );
  
  std::vector< std::size_t > keys;
  keys.reserve( sico::utl::ipow( 2 * nrad + 1, dim ) );

  std::vector< unsigned int > idx_low ( dim ), idx_hgh ( dim );

  // std::cout << "Rad = " << rad;
  // // std::cout << "\niRad = " << nrad << "\nPos = ( ";
  // for ( auto && _c : coords )
  //   std::cout << _c << " ";
  // std::cout << ")\niPos = ( ";
  // find range of indexes in each dimension
  for ( unsigned short ii = 0; ii < dim; ++ii ) {

    // find position from float coords:    
    int pos = int( ( coords[ ii ] - _boxmin ) * _expand );

    // set limits:
    // idx_low[ ii ] = ( pos - nrad + idx_max ) % idx_max; // periodic
    idx_low[ ii ] = ( pos - nrad ) >= 0 ? pos - nrad : 0;
    // idx_hgh[ ii ] = ( pos + nrad + idx_max ) % idx_max; // periodic
    idx_hgh[ ii ] = ( pos + nrad );

    // std::cout << pos << " [ " << idx_low[ ii ] << ", " << idx_hgh[ ii ] << " ] ";
    
  }
  // std::cout << ")" << std::endl;

  root->find_in_range( idx_low, idx_hgh, keys );
  
  return std::vector< std::size_t >{ keys.begin(), keys.end() };
  
}

// ===============================================================
