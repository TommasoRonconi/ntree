#include <iostream>
#include <ntree_ds.h>
#include <fstream>

int main () {

  const size_t dim = 2;
  const size_t depth = 8;

  std::vector< double > coord;
  double _c;
  while ( std::cin >> _c ) coord.emplace_back( _c );
  
  try {

    // =============================================================
    // Build tree:
    
    sico::utl::ntree< dim, depth > tree2d { coord, 0., 4. };

    // =============================================================
    // Store all keys:

    std::vector< std::size_t > all_keys;
    for ( auto && _c : tree2d ) 
      all_keys.emplace_back( _c->particle->h_key );

    // =============================================================
    // Read reference file:

    std::string file_in = "/home/tomi/phd/repos/128_pos_search_run2.ref";
    std::ifstream fin { file_in.c_str() };
    
    std::vector< int > idx_keys;
    std::vector< double > ref_coord;
    std::vector< double > pos ( 2 );
    double rad, xref, yref;
    std::size_t key;
    
    fin >> pos[ 0 ] >> pos[ 1 ] >> rad;
    while ( fin >> key >> xref >> yref ) {
      idx_keys.push_back( key );
      ref_coord.push_back( xref );
      ref_coord.push_back( yref );
    }
    fin.clear(); fin.close();

    // =============================================================
    // find in radius:
    
    auto vect = tree2d.find( pos, rad );

    std::cout << "I have found " << vect.size() << " keys\n";

    bool allfound = true;
    for ( auto && ik : idx_keys ) {
      auto it = std::find( vect.begin(), vect.end(), all_keys[ ik ] );
      if ( it == vect.end() ) {
	allfound = false;
	std::cout << "Key " << all_keys[ ik ] << " not found!";
	auto check = tree2d.find( all_keys[ ik ] );
	if ( *check ) {
	  std::cout << " But it exists!!!\n";
	  std::cout << "Cell-limits:\n";
	  for ( unsigned short ii = 0; ii < dim; ++ii )
	    std::cout << "\t" << check->_cell_min[ ii ] << " - " << check->_cell_max[ ii ] << "\n";
	}
	else
	  std::cout << " And it is not in the tree, damn!\n";
      }
    }
    if ( allfound ) 
      std::cout << "All " << idx_keys.size() << " reference keys found: YAY!!\n";
    
  }
  catch ( sico_err::size_invalid er ) {
    std::cout << er.message << "\n";
  }
  catch ( ... ) {
    std::cout << "Exception occurred\n";
  }
  
  return 0;

}
