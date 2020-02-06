#include <iostream>
#include <ncell.h>
#include <hilbert_curve.h>

int main () {

  sico::utl::ncell< 2 > cell2d {};
  sico::utl::ncell< 3 > cell3d {};
  sico::utl::ncell< 4 > cell4d {};

  // std::cout << cell2d.sub_cell.size() << "\t" << cell3d.sub_cell.size() << "\t" << cell4d.sub_cell.size() << std::endl;

  hilbert_curve< 2, 4 > hc {};
  hilbert_coord_t< 2, 4 > pos0 = { 0, 1 };
  hilbert_coord_t< 2, 4 > pos1 = { 1, 0 };
  hilbert_coord_t< 2, 4 > pos2 = { 2, 1 };
  hilbert_coord_t< 2, 4 > pos3 = { 3, 3 };
  hilbert_coord_t< 2, 4 > pos4 = { 0, 2 };
  hilbert_coord_t< 2, 4 >
    grid0 = hc.get_grid( pos0 ),
    grid1 = hc.get_grid( pos1 ),
    grid2 = hc.get_grid( pos2 ),
    grid3 = hc.get_grid( pos3 ),
    grid4 = hc.get_grid( pos4 );
  
  size_t
    key0 = hc.get_key( grid0 ).to_ulong(),
    key1 = hc.get_key( grid1 ).to_ulong(),
    key2 = hc.get_key( grid2 ).to_ulong(),
    key3 = hc.get_key( grid3 ).to_ulong(),
    key4 = hc.get_key( grid4 ).to_ulong();

  std::vector< sico::utl::nparticle< 2 > * > bucket (5);
  std::vector< std::size_t >
    coord0 = pos0(),
    coord1 = pos1(),
    coord2 = pos2(),
    coord3 = pos3(),
    coord4 = pos4();
  std::cout
    << coord0[ 0 ] << "\t" << coord0[ 1 ] << "\t" << key0 << "\n"
    << coord1[ 0 ] << "\t" << coord1[ 1 ] << "\t" << key1 << "\n"
    << coord2[ 0 ] << "\t" << coord2[ 1 ] << "\t" << key2 << "\n"
    << coord3[ 0 ] << "\t" << coord3[ 1 ] << "\t" << key3 << "\n"
    << coord4[ 0 ] << "\t" << coord4[ 1 ] << "\t" << key4 << "\n";
  
  bucket[ 0 ] = new sico::utl::nparticle< 2 > { coord0, key0 };
  bucket[ 1 ] = new sico::utl::nparticle< 2 > { coord1, key1 };
  bucket[ 2 ] = new sico::utl::nparticle< 2 > { coord2, key2 };
  bucket[ 3 ] = new sico::utl::nparticle< 2 > { coord3, key3 };
  bucket[ 4 ] = new sico::utl::nparticle< 2 > { coord4, key4 };
  std::sort( bucket.begin(), bucket.end(),
	     [&]( sico::utl::nparticle< 2 > * a,
		  sico::utl::nparticle< 2 > * b ){
	       return a->h_key < b->h_key;
	     } );
  std::cout << "\n"
    << bucket[ 0 ]->coord[ 0 ] << "\t" << bucket[ 0 ]->coord[ 1 ] << "\t" << bucket[ 0 ]->h_key << "\n"
    << bucket[ 1 ]->coord[ 0 ] << "\t" << bucket[ 1 ]->coord[ 1 ] << "\t" << bucket[ 1 ]->h_key << "\n"
    << bucket[ 2 ]->coord[ 0 ] << "\t" << bucket[ 2 ]->coord[ 1 ] << "\t" << bucket[ 2 ]->h_key << "\n"
    << bucket[ 3 ]->coord[ 0 ] << "\t" << bucket[ 3 ]->coord[ 1 ] << "\t" << bucket[ 3 ]->h_key << "\n"
    << bucket[ 4 ]->coord[ 0 ] << "\t" << bucket[ 4 ]->coord[ 1 ] << "\t" << bucket[ 4 ]->h_key << "\n";

  cell2d.insert( bucket );

  return 0;

}
