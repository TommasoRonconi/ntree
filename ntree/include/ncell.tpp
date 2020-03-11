// ===============================================================

template< const size_t dim, const size_t depth >
void ncell< dim, depth >::insert ( const std::vector< nparticle< dim, depth > * > & bucket ) {

  auto start = bucket.begin();

  // this loop iterates on the 2^dim sub-cells:
  for ( short ic = 0; ic < ( 1 << dim ); ++ic ) {

    // finds iterator to last position for current cell
    auto stop { std::upper_bound( start, bucket.end(), ic,
				  [ & ] ( const short & a, nparticle< dim, depth > * b ){
				    return a < hash_func( b->h_key );
				  } ) };
    
    // compute lenght of sub-vector
    auto dist = std::distance( start, stop );
    
    // if sub-vector not empty, dig deeper ( recursion! )
    if ( dist > 1 ) {
      
      // initialize the sub-cell
      sub_cell[ ic ].reset( new ncell< dim, depth > { _level + 1, this } );

      // call recursion
      sub_cell[ ic ]->insert( std::vector< nparticle< dim, depth > * > { start, stop } );
      
    }
    
    // set the particle if only one is contained in the sub-vector
    else if ( dist == 1 )
      sub_cell[ ic ].reset( new ncell< dim, depth > { *start, _level + 1, this } );

    // reset start iterator for next sub-cell
    start = stop;
    
  }

}

// ===============================================================

template< const size_t dim, const size_t depth >
void ncell< dim, depth >::set_limits ( const std::size_t keyloc,
				       const hilbert_curve< dim, depth > & hloc) {

  // number of thinnest gridcells in each cell:
  std::size_t Lcell = 1 << ( depth - _level );

  // get the local axes:
  auto _gridloc = hloc.get_grid_from_key( keyloc );
  auto _axesloc = hloc.get_axes( _gridloc );

  if ( _parent )
    for ( unsigned short ii = 0; ii < dim; ++ii ) {
      std::size_t ax = _axesloc( ii ) - ( _axesloc( ii ) % Lcell );
      _cell_min[ ii ] = ax;
      _cell_max[ ii ] = ax + Lcell;
    }
  else {
    _cell_min = std::vector< std::size_t >( dim, 0 );
    _cell_max = std::vector< std::size_t >( dim, Lcell );
  }
  
  // this loop iterates on the 2^dim sub-cells:
  // if sub-cell ic-th exists -> call recursion.
  for ( short ic = 0; ic < ( 1 << dim ); ++ic ) 
    if ( sub_cell[ ic ] ) {
      std::size_t new_key = keyloc + ic * ipow( Lcell >> 1, dim );
      sub_cell[ ic ]->set_limits( new_key, hloc );
    }

  return;
  
}

// ===============================================================

template< const size_t dim, const size_t depth >
void ncell< dim, depth >::clear () {

  // if current cell contains a particle
  // there are no deeper cells
  if ( particle )
    particle.reset();

  // otherwise call recursion from each sub-cell
  // then reset it
  else {
    for ( auto & sub : sub_cell )
      if ( sub ) {
	sub->clear();
	sub.reset();
      }
  }
  return;
  
}

// ===============================================================

template< const size_t dim, const size_t depth >
void ncell< dim, depth >::dump_all ( std::vector< std::size_t > & keys ) {

  auto here = ncell< dim, depth >::iterator{ leftmost() };
  auto last = ncell< dim, depth >::iterator{ rightmost() };

  while ( here != last ) {
    keys.emplace_back( here->particle->h_key );
    ++here;
  }
  keys.emplace_back( last->particle->h_key );
  
  return;

}

// ===============================================================

template< const size_t dim, const size_t depth >
ncell< dim, depth > * ncell< dim, depth >::leftmost () {

  // if current cell contains particle,
  // there are no deeper cells
  if ( particle )
    return this;

  // otherwise call recursion from first
  // not null sub-cell
  for ( short ic = 0; ic < ( 1 << dim ); ++ic )
    if ( sub_cell[ ic ] )
      return sub_cell[ ic ]->leftmost();

  // if nor this cell nor its sub-cells contain
  // any particle, return null
  return nullptr;

}

// ===============================================================

template< const size_t dim, const size_t depth >
ncell< dim, depth > * ncell< dim, depth >::rightmost () {

  // if current cell contains particle,
  // there are no deeper cells
  if ( particle ) return this;

  // otherwise call recursion from last
  // not null sub-cell
  for ( short ic = ( 1 << dim ) - 1; 0 <= ic; --ic )
    if ( sub_cell[ ic ] ) 
      return sub_cell[ ic ]->rightmost();

  // if nor this cell nor its sub-cells contain
  // any particle, return null
  return nullptr;

}

// ===============================================================

template< const size_t dim, const size_t depth >
ncell< dim, depth > * ncell< dim, depth >::find ( const size_t key ) {

  // if current cell contains particle return this if the key is right
  if ( particle && ( particle->h_key == key ) ) return this;

  // otherwise search in the right sub-cell, by using
  // hash function for current level
  else {

    short ic { hash_func( key ) };
    if ( sub_cell[ ic ] )
      return sub_cell[ ic ]->find( key );

    // if no particle with given key is found
    else 
      return nullptr;
  }
    
}

// ===============================================================

template< const size_t dim, const size_t depth >
ncell< dim, depth > * ncell< dim, depth >::find_prev ( const size_t key ) {

  // go to higher level
  auto high_lev = _parent;

  // if higher level is not null
  if ( high_lev ) {

    // search in sub-cells, starting from prev one
    short ic = high_lev->hash_func( key ) - 1;
    for ( ; 0 <= ic; --ic )
      if ( high_lev->sub_cell[ ic ] )
	return high_lev->sub_cell[ ic ]->rightmost();

    // rise one level up
    return high_lev->find_prev( key );
    
  }

  // if the highest level is reached and no
  // particle is found
  else
    return nullptr;

}

// ===============================================================

template< const size_t dim, const size_t depth >
ncell< dim, depth > * ncell< dim, depth >::find_next ( const size_t key ) {

  // go to higher level
  auto high_lev = _parent;

  // if higher level is not null
  if ( high_lev ) {

    // search in sub-cells, starting from next one
    short ic = high_lev->hash_func( key ) + 1;
    for ( ; ic < ( 1 << dim ); ++ic )
      if ( high_lev->sub_cell[ ic ] )
	return high_lev->sub_cell[ ic ]->leftmost();

    // rise one level up
    return high_lev->find_next( key );
    
  }

  // if the highest level is reached and no
  // particle is found
  else
    return nullptr;

}

// ===============================================================

template< const size_t dim, const size_t depth >
void ncell< dim, depth >::find_in_range ( const std::vector< unsigned int > minima,
					  const std::vector< unsigned int > maxima,
					  std::vector< std::size_t > & keys,
					  const unsigned int idx_max ) {

  bool any = true;
  bool all = true;
  int Lcell = 1 << ( depth - _level );

  // periodic:
  for ( unsigned short ii = 0; ii < dim; ++ii ) {

    int dist = metric( maxima[ ii ], minima[ ii ], idx_max );
    
    // this should go away:
    int
      min  = minima[ ii ],
      max  = maxima[ ii ], 
      cmin = _cell_min[ ii ],
      cmax = _cell_max[ ii ];

    bool all1d = ( ( ( metric( cmin, min, idx_max ) + metric( max, cmin, idx_max ) ) == dist ) &&
		   ( ( metric( cmax, min, idx_max ) + metric( max, cmax, idx_max ) ) == dist ) &&
		   ( Lcell <= dist ) );
    
    any &= all1d || ( ( ( metric( min, cmin, idx_max ) + metric( cmax, min, idx_max ) ) == Lcell ) ||
		      ( ( metric( max, cmin, idx_max ) + metric( cmax, max, idx_max ) ) == Lcell ) );
  
    all &= all1d;

  }
  
  // not periodic:
  // for ( unsigned short ii = 0; ii < dim; ++ii ) {

  //   bool all1d = ( ( minima[ ii ] <= _cell_min[ ii ] ) &&
  // 		   ( _cell_max[ ii ] < maxima[ ii ] ) );
    
  //   any &=
  //     all1d != (
  // 		( ( _cell_min[ ii ] < minima[ ii ] ) &&
  // 		  ( minima[ ii ] <= _cell_max[ ii ] )  ) ||
  // 		( ( _cell_min[ ii ] < maxima[ ii ] ) &&
  // 		  ( maxima[ ii ] <= _cell_max[ ii ] ) ) );
  
  //   all &= all1d;

  // }

  // store all particles:
  if ( all ) 
    dump_all( keys );
  
  else if ( any ) {

    // if leaf-cell -> store key:
    if ( particle ) 
      keys.emplace_back( particle->h_key );
    
    // else -> call recursion from (existing) sub-cells
    else 
      for ( auto && sc : sub_cell )
	if ( sc )
	  sc->find_in_range( minima, maxima, keys, idx_max );
    
  } // end if ( any )

  return;

}

// ===============================================================
