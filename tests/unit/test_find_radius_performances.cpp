#include <iostream>
#include <ntree_ds.h>
#include <chrono>
#include <cstdlib>
typedef std::chrono::high_resolution_clock Clock;

int main () {

  const size_t dim = 2;
  const size_t depth = 16;

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
    for ( auto && _c : tree2d ) {
      // auto hgrid = tree2d._hc.get_grid( _c->particle->h_coord );
      std::cout <<
	_c->particle->pos[ 0 ] << "\t" <<
	_c->particle->pos[ 1 ] << "\t" <<
	_c->particle->h_coord( 0 ) << "\t" <<
	_c->particle->h_coord( 1 ) << "\t" <<
        // hgrid[ 0 ] << "\t" <<
        // hgrid[ 1 ] << "\t" <<
        // hgrid[ 0 ].to_ulong() << "\t" <<
        // hgrid[ 1 ].to_ulong() << "\t" <<
	_c->particle->h_key << "\n";
    }

    // =============================================================
    // find in radius:

    auto time_start = Clock::now();
    auto vect = tree2d.find( { 0.7, 2.3 }, 0.8 );
    auto time_end = Clock::now();

    double time_run = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();

    std::cout << "\nTime spent\t" << time_run << " nsec\n";

    std::cout << "\nkeys found: " << vect.size() << "\n";

    // std::cout << "\nkeys found:\t" << vect.size() << "\n";
    // for ( auto && _k : vect )
    //   std::cout << _k << "\t";
    // std::cout << "( should be 3, 4, 10 )\n";
    
  }
  catch ( sico_err::size_invalid er ) {
    std::cout << er.message << "\n";
  }
  catch ( ... ) {
    std::cout << "Exception occurred\n";
  }
  
  return 0;

}
