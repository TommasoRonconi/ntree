#include <iostream>
#include <ncell.h>
#include <hilbert_curve.h>
#include <chrono>
#include <cstdlib>
typedef std::chrono::high_resolution_clock Clock;

int main () {

  const std::size_t depth = 16;

  // check c.tors:
  sico::utl::ncell< 2, depth > cell2d {};
  
  // builds the hilbert grid:
  hilbert_curve< 2, depth > hc {};
  std::vector< std::size_t > pos0 = { 0, 1 };
  std::vector< std::size_t > pos1 = { 1, 0 };
  std::vector< std::size_t > pos2 = { 2, 1 };
  std::vector< std::size_t > pos3 = { 3, 3 };
  std::vector< std::size_t > pos4 = { 0, 2 };
  std::vector< std::size_t > pos5 = { 2, 0 };

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
  
  auto next = cell2d.leftmost();

  while ( next ) {

    std::cout <<
      next->particle->h_coord( 0 ) << "\t" <<
      next->particle->h_coord( 1 ) << "\t" <<
      next->particle->h_key << "\n";

    next = next->find_next( next->particle->h_key );

  }
  std::cout << "\n";

  // =====================================================================================
  // check set_limits();

  auto time_start = Clock::now();  
  cell2d.set_limits( 0, hc );
  auto time_end = Clock::now();

  double time_run = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count();

  std::cout << "\nTime spent\t" << time_run << " nsec\n";  

  return 0;

}
