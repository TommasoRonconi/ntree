// ===============================================================

template< const size_t dim, const size_t depth >
ntree< dim, depth >::ntree ( const std::vector< double > & coords,
			     const double & boxmin,
			     const double & boxmax ) :
  _boxmin{ boxmin }, _boxmax{ boxmax },
  _lenght{ ( boxmax - boxmin ) / ( 1 << depth ) },
  _expand{ 1. / _lenght }  
{

  if ( coords.size() > dim * ( 1 << depth ) )
    throw sico_err::size_invalid( "The provided vector of coordinates is too big for your choice of the template parameters." );
  
// #pragma omp parallel for
//   for ( )

}

// ===============================================================
