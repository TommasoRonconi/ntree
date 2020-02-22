#include <iostream>
#include <ncell.h>
#include <hilbert_curve.h>

int main () {

  const std::size_t depth = 2;

  // check c.tors:
  sico::utl::ncell< 2, depth > cell2d {};
  sico::utl::ncell< 3, depth > cell3d {};
  sico::utl::ncell< 4, depth > cell4d {};

  std::cout << cell2d.sub_cell.size() << "\t" << cell3d.sub_cell.size() << "\t" << cell4d.sub_cell.size() << "\t(should be 4, 8, 16)\n";

  // builds the hilbert grid:
  hilbert_curve< 2, depth > hc {};
  hilbert_coord_t< 2, depth > pos0 = { 0, 1 };
  hilbert_coord_t< 2, depth > pos1 = { 1, 0 };
  hilbert_coord_t< 2, depth > pos2 = { 2, 1 };
  hilbert_coord_t< 2, depth > pos3 = { 3, 3 };
  hilbert_coord_t< 2, depth > pos4 = { 0, 2 };
  hilbert_coord_t< 2, depth > pos5 = { 2, 0 };

  hilbert_coord_t< 2, depth >
    grid0 = hc.get_grid( pos0 ),
    grid1 = hc.get_grid( pos1 ),
    grid2 = hc.get_grid( pos2 ),
    grid3 = hc.get_grid( pos3 ),
    grid4 = hc.get_grid( pos4 ),
    grid5 = hc.get_grid( pos5 );
  
  std::size_t
    key0 = hc.get_key( grid0 ).to_ulong(),
    key1 = hc.get_key( grid1 ).to_ulong(),
    key2 = hc.get_key( grid2 ).to_ulong(),
    key3 = hc.get_key( grid3 ).to_ulong(),
    key4 = hc.get_key( grid4 ).to_ulong(),
    key5 = hc.get_key( grid5 ).to_ulong();
  
  std::cout << "\nShould be a list of integers with random ordering of third column:\n"
    << pos0( 0 ) << "\t" << pos0( 1 ) << "\t" << key0 << "\n"
    << pos1( 0 ) << "\t" << pos1( 1 ) << "\t" << key1 << "\n"
    << pos2( 0 ) << "\t" << pos2( 1 ) << "\t" << key2 << "\n"
    << pos3( 0 ) << "\t" << pos3( 1 ) << "\t" << key3 << "\n"
    << pos4( 0 ) << "\t" << pos4( 1 ) << "\t" << key4 << "\n"
    << pos5( 0 ) << "\t" << pos5( 1 ) << "\t" << key5 << "\n";

  std::vector< sico::utl::nparticle< 2, depth > * > bucket = {  
    new sico::utl::nparticle< 2, depth > { pos0, key0 },
    new sico::utl::nparticle< 2, depth > { pos1, key1 },
    new sico::utl::nparticle< 2, depth > { pos2, key2 },
    new sico::utl::nparticle< 2, depth > { pos3, key3 },
    new sico::utl::nparticle< 2, depth > { pos4, key4 },
    new sico::utl::nparticle< 2, depth > { pos5, key5 }
  };
  
  std::sort( bucket.begin(), bucket.end(),
	     [&]( sico::utl::nparticle< 2, depth > * a,
		  sico::utl::nparticle< 2, depth > * b ){
	       return a->h_key < b->h_key;
	     } );
  std::cout << "\nshould be ordered w.r.t. third column:\n";
  for ( auto && _b : bucket ) 
    std::cout << _b->h_coord( 0 ) << "\t" << _b->h_coord( 1 ) << "\t" << _b->h_key << "\n";
  std::cout << "\n";

  // =====================================================================================
  // check insert();
  cell2d.insert( bucket );

  // =====================================================================================
  // check leftmost():
  auto leftcell = cell2d.leftmost();

  if ( leftcell )
    std::cout << "first cell:\t" << leftcell->particle->h_key << "\t(should be 1)\n";

  // =====================================================================================
  // check rightmost():
  auto rightcell = cell2d.rightmost();
 
  if ( rightcell )
    std::cout << "last cell:\t" << rightcell->particle->h_key << "\t(should be 14)\n";

  // =====================================================================================
  // check find_next( key ):
  auto second = leftcell->find_next( leftcell->particle->h_key );

  if ( second )
    std::cout << "second cell:\t" << second->particle->h_key << "\t(should be 3)\n";

  auto check_cell = leftcell->find_next( 2 );
  if ( check_cell )
    std::cout << "check-cell:\t" << check_cell->particle->h_key << "\t(should be 3)\n";

  // =====================================================================================
  // check find_prev( key ):

  auto prev = second->find_prev( second->particle->h_key );

  if ( prev )
    std::cout << "first cell:\t" << prev->particle->h_key << "\t(should be 1)\n";  

  // =====================================================================================
  // check everything is in-place:

  auto current = leftcell;
  std::cout << "\ncheck that all particles are in place:";
  while ( current ) {
    std::cout << "\t" << current->particle->h_key;
    current = current->find_next( current->particle->h_key );
  }
  std::cout << "\n\n";

  // =====================================================================================
  // check find( key ):
  auto existing_cell = cell2d.find( 10 );

  if ( existing_cell )
    std::cout << "find check:\t" << existing_cell->particle->h_key << "\t(should be 10)\n";

  existing_cell = existing_cell->find_next( existing_cell->particle->h_key );
  if ( existing_cell )
    std::cout << "find check:\t" << existing_cell->particle->h_key << "\t(should be 13)\n";  
  
  auto nonexisting_cell = cell2d.find( 5 );

  if ( nonexisting_cell )
    std::cout << "find check:\t" << nonexisting_cell->particle->h_key << "\t(this should not happen)\n";
  else
    std::cout << "find check:\tok!\n";

  // =====================================================================================
  // check clear():
  cell2d.clear();

  leftcell = cell2d.leftmost();
  if ( leftcell )
    std::cout << leftcell->particle->h_key << std::endl;
  else
    std::cout << "all clear\n";

  // =====================================================================================
  // checks d.tor():
  return 0;

}
