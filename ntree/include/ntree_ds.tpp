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
  if ( coords.size() > dim * ( 1 << depth ) )
    throw sico_err::size_invalid( "The provided vector of coordinates is too big ( size = " +
				  std::to_string( coords.size() ) +
				  " ) for your choice of the template parameters." );
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
    bucket[ ii ] = new nparticle< dim, depth > { hpos, coords,
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

}

// ===============================================================
