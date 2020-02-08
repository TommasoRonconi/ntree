#include <iostream>
#include <ntree_ds.h>

int main () {

  const size_t dim = 2;
  const size_t depth = 2;

  // check default constructor
  sico::utl::ntree< dim, depth > tree2d_c {};
  sico::utl::ntree< 3, depth > tree3d_c;

  // create a list of positions:

  std::vector< double > coord = { 0.5, 1.5,
				  1.5, 0.5,
				  2.5, 1.5,
				  3.5, 3.5,
				  0.5, 2.5,
				  2.5, 0.5 };
  
  // check build-tree constructor
  try {
    sico::utl::ntree< dim, depth > tree2d { coord, 0., 4. };

    // for ( auto it = tree2d.begin(); it != tree2d.end(); ++it ) 
    for ( auto && _c : tree2d )
      std::cout <<
	_c->particle->pos[ 0 ] << "\t" <<
	_c->particle->pos[ 1 ] << "\t" <<
	_c->particle->h_coord( 0 ) << "\t" <<
	_c->particle->h_coord( 1 ) << "\t" <<
	_c->particle->h_key << "\n";
    
  }
  catch ( sico_err::size_invalid er ) {
    std::cout << er.message << "\n";
  }
  catch ( ... ) {
    std::cout << "Exception occurred\n";
  }
  
  return 0;

}
