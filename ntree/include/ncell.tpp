// ===============================================================

template< const size_t dim >
void ncell< dim >::clear () {

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

template< const size_t dim >
void ncell< dim >::insert ( const std::vector< nparticle< dim > * > & bucket ) {

  // std::cout << "check enter: level = " << _level << ", bucket.size() = " << bucket.size() << "\n";

  auto start = bucket.begin();

  // this loop iterates on the 2^dimension sub-cells:
  for ( short ic = 0; ic < sico::utl::bitset( 0, dim ); ++ic ) {

    // finds iterator to last position for current cell
    auto stop { std::upper_bound( start, bucket.end(), ic,
				  [&] ( const short & a, nparticle< dim > * b ){
				    return a < hash_func( b->z_key );
				  } ) };
    
    // compute lenght of sub-vector
    auto dist = std::distance( start, stop );
    
    // std::cout << "\tlevel = " << _level << ", subcell = " << ic << ", distance = " << dist << "\n";
    
    // if sub-vector not empty, dig deeper ( recursion! )
    if ( dist > 1 ) {
      
      // initialize the sub-cell
      sub_cell[ic].reset( new ncell< dim > { _level - 1, this } );

      // call recursion
      sub_cell[ic]->insert( std::vector< nparticle< dim > * > { start, stop } );
      
    }
    
    // set the particle if only one is contained in the sub-vector
    else if ( dist == 1 )
      sub_cell[ic].reset( new ncell< dim > { *start, _level - 1, this } );

    // reset start iterator for next sub-cell
    start = stop;
    
  }
  // std::cout << "check exit: level = " << _level << ", bucket.size() = " << bucket.size() << "\n";

}

// ===============================================================

template< const size_t dim >
ncell< dim > * ncell< dim >::find ( const size_t key ) {

  // if current cell contains particle return this
  if ( particle )
    return this;

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

template< const size_t dim >
ncell< dim > * ncell< dim >::find_next ( const size_t key ) {

  // go to higher level
  auto high_lev = _parent;

  // if higher level is not null
  if ( high_lev ) {

    // search in sub-cells, starting from next one
    short ic = high_lev->hash_func( key ) + 1;
    for (; ic < bitset( 0, dim ); ++ic ) 
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

template< const size_t dim >
ncell< dim > * ncell< dim >::leftmost () {

  // if current cell contains particle,
  // there'are no deeper cells
  if ( particle )
    return this;

  // otherwise call recursion from first
  // not null sub-cell
  for ( short ic = 0; ic < bitset( 0, dim ); ++ic )
    if ( sub_cell[ ic ] )
      return sub_cell[ ic ]->leftmost();

  // think whether you need this:
  // return nullptr;

}

// ===============================================================
