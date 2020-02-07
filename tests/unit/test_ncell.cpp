#include <iostream>
#include <ncell.h>
#include <hilbert_curve.h>

int main () {

  const std::size_t depth = 2;

  // check c.tors:
  sico::utl::ncell< 2, depth > cell2d {};
  sico::utl::ncell< 3, depth > cell3d {};
  sico::utl::ncell< 4, depth > cell4d {};

  std::cout << cell2d.sub_cell.size() << "\t" << cell3d.sub_cell.size() << "\t" << cell4d.sub_cell.size() << std::endl;

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
  
  size_t
    key0 = hc.get_key( grid0 ).to_ulong(),
    key1 = hc.get_key( grid1 ).to_ulong(),
    key2 = hc.get_key( grid2 ).to_ulong(),
    key3 = hc.get_key( grid3 ).to_ulong(),
    key4 = hc.get_key( grid4 ).to_ulong(),
    key5 = hc.get_key( grid5 ).to_ulong();

  std::vector< std::size_t >
    coord0 = pos0(),
    coord1 = pos1(),
    coord2 = pos2(),
    coord3 = pos3(),
    coord4 = pos4(),
    coord5 = pos5();
  std::cout
    << coord0[ 0 ] << "\t" << coord0[ 1 ] << "\t" << key0 << "\n"
    << coord1[ 0 ] << "\t" << coord1[ 1 ] << "\t" << key1 << "\n"
    << coord2[ 0 ] << "\t" << coord2[ 1 ] << "\t" << key2 << "\n"
    << coord3[ 0 ] << "\t" << coord3[ 1 ] << "\t" << key3 << "\n"
    << coord4[ 0 ] << "\t" << coord4[ 1 ] << "\t" << key4 << "\n"
    << coord5[ 0 ] << "\t" << coord5[ 1 ] << "\t" << key5 << "\n";

  std::vector< sico::utl::nparticle< 2 > * > bucket = {  
    new sico::utl::nparticle< 2 > { coord0, key0 },
    new sico::utl::nparticle< 2 > { coord1, key1 },
    new sico::utl::nparticle< 2 > { coord2, key2 },
    new sico::utl::nparticle< 2 > { coord3, key3 },
    new sico::utl::nparticle< 2 > { coord4, key4 },
    new sico::utl::nparticle< 2 > { coord5, key5 }
  };
  
  std::sort( bucket.begin(), bucket.end(),
	     [&]( sico::utl::nparticle< 2 > * a,
		  sico::utl::nparticle< 2 > * b ){
	       return a->h_key < b->h_key;
	     } );
  std::cout << "\n";
  for ( auto && _b : bucket ) 
    std::cout << _b->coord[ 0 ] << "\t" << _b->coord[ 1 ] << "\t" << _b->h_key << "\n";

  // check insert();
  cell2d.insert( bucket );

  // check leftmost():
  auto leftcell = cell2d.leftmost();

  if ( leftcell )
    std::cout << leftcell->particle->h_key << std::endl;


  // check clear():
  cell2d.clear();

  leftcell = cell2d.leftmost();
  if ( leftcell )
    std::cout << leftcell->particle->h_key << std::endl;
  else
    std::cout << "all clear\n";

  // checks d.tor():
  return 0;

}
