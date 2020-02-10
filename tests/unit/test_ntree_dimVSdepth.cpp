#include <iostream>
#include <ntree_ds.h>

int main ( int argc, char** argv ) {

  std::string input;
  if ( argc != 2 ) {
    std::cerr << "Error! I need a file path!!\n";
    std::exit( 1 );
  }
  else input = argv[ 1 ];
  
  const size_t dim = 2;
  const size_t depth = 16;

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

    // =============================================================
    // c.tor
    
    sico::utl::ntree< dim, depth > tree2d { coord, 0., 4. };

    // for ( auto it = tree2d.begin(); it != tree2d.end(); ++it ) 
    for ( auto && _c : tree2d )
      std::cout <<
  	_c->particle->pos[ 0 ] << "\t" <<
  	_c->particle->pos[ 1 ] << "\t" <<
  	_c->particle->h_coord( 0 ) << "\t" <<
  	_c->particle->h_coord( 1 ) << "\t" <<
  	_c->particle->h_key << "\n";

    // =============================================================
    // find key

    auto cell = tree2d.find( 1118481066 );
    std::cout << "check tree.find( 1118481066 ):\t" << cell->particle->h_key << " (should be 1118481066)\n";

    // =============================================================
    // find position:

    // cell = tree2d.find( { 1.7, 2.3 } );
    // if ( *cell ) 
    //   std::cout << "check tree.find( { 1.7, 2.3 } ):\t" << cell->particle->h_key << " (this doesn't happen)\n";
    // else
    //   std::cout << "check tree.find( { 1.7, 2.3 } ):\tok!\n";
    // cell = tree2d.find( { 0.7, 1.61 } );
    // if ( *cell )
    //   std::cout << "check tree.find( { 0.7, 1.61 } ):\t" << cell->particle->h_key << " (this should be 3)\n";
    // else
    //   std::cout << "check tree.find( { 0.7, 1.61 } ):\tNOT ok!\n";

    // =============================================================
    // find in radius:

    auto vect = tree2d.find( { 0.7, 2.3 }, 0.8 );

    std::cout << "\nkeys found:\t" << vect.size() << "\n";
    for ( auto && _k : vect )
      std::cout << _k << "\t";
    std::cout << "( should be 3, 4, 10 )\n";
    
  } // end try scope
  catch ( sico_err::size_invalid er ) {
    std::cout << er.message << "\n";
  }
  catch ( ... ) {
    std::cout << "Exception occurred\n";
  }
  
  return 0;

}
