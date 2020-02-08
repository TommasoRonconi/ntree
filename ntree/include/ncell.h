#ifndef __NCELL__
#define __NCELL__

#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <string>

// #include <error_handling.h>
#include <bit_manipulator.h>
#include <hilbert_curve.h>

namespace sico {

  namespace utl {

    template < const size_t dim = 2, const size_t depth = 2 >
    struct nparticle {

      hilbert_coord_t< dim, depth > h_coord {}; //= hilbert_coord_t< dim, depth >{};
      
      std::vector< double > pos = std::vector< double >( dim );

      std::size_t h_key;

      nparticle ( const hilbert_coord_t< dim, depth> & coord,
		  const std::size_t & key ) : h_coord{ coord }, h_key{ key } {}

      nparticle ( const hilbert_coord_t< dim, depth> & coord,
		  const std::vector< double > & position,
		  const std::size_t & key ) : h_coord{ coord },
					      pos{ position },
					      h_key{ key }
      {

      	if ( position.size() != dim )
      	  throw sico_err::size_invalid( "Miss-matching dimension between template value" +
      					std::to_string( dim ) + " and size of position.size = " +
      					std::to_string( position.size() ) );	

      }

      ~nparticle () = default;

      bool cmp_key ( const nparticle & a, const nparticle & b ) { return ( a.h_key < b.h_key ); }

      bool eqv_key ( const nparticle & a, const nparticle & b ) { return ( a.h_key == b.h_key ); }

      bool eqv_pos ( const nparticle & a, const nparticle & b ) {

	bool ret_val = true;

	for ( size_t ii = 0; ii < dim; ++ii )
	  ret_val = ret_val && ( abs( a.coord[ ii ] - b.coord[ ii ] ) < 1.e-16 );
	
	return ret_val;

      }
  
    }; // endstruct nparticle

    template < const size_t dim = 2, const size_t depth = 2 > 
    struct ncell {

      std::size_t _level;

      ncell * _parent = nullptr;

      /// by initializing a vector of pointers it will have size 4 and all the 4 elements will be
      /// initialized to the default value ( which is 'nullptr', as I wish ).
      /// instead initializing like 'vector< unique_ptr< T > > ( size, value )' has to make a
      /// copy of 'value' for each element, thus it is less efficient.
      std::vector< std::unique_ptr< ncell > > sub_cell =
	std::vector< std::unique_ptr< ncell > >( 1 << dim );

      std::unique_ptr< nparticle< dim, depth > > particle = nullptr;

      //public:

      // this serves as default constructor:
      ncell ( std::size_t level = 0, ncell * parent = nullptr )
	: _level{ level }, _parent { parent } {}

      ncell ( nparticle< dim, depth > * new_particle,
	      std::size_t level = 0, ncell * parent = nullptr )
	: _level{ level }, _parent { parent } {

	  particle.reset( new_particle );
    
	}

      ~ncell() noexcept = default;

      // to implement this, need to overload operator- in class iterator:
      // size_t size () { return end() - begin(); }
  
      void insert ( const std::vector< nparticle< dim, depth > * > & parts );

      short hash_func ( const size_t key ) {

	return bits( key, dim * ( depth - _level - 1 ), dim );

      }

      // clears up everything from the current cell and below
      void clear ();

      ncell * find ( const size_t key );

      // starting from a known cell gets you to the next occupied one
      // (Warning: this might mess-up stuff if the key is not selected accurately,
      //           no error nor exception is raised independently of the key provided
      //           but behaviour is undefined in case the key is not within the range)
      ncell * find_next ( const size_t key );

      // starting from the current cell gets you to the
      // first occupied one, following the hilbert ordering
      ncell * leftmost ();

    }; // endclass ncell

    template< const size_t dim = 2, const size_t depth = 2 >
    class iterator {

      ncell< dim, depth > * current;

    public:

      iterator () noexcept = default;

      iterator ( ncell< dim, depth > * cl ) : current{ cl } {}

      ~iterator () noexcept = default;

      ncell< dim, depth > * operator*() { return current; }

      iterator & operator++ () {

	current = current->find_next( current->particle->h_key );

	return *this;

      }

    }; // endclass iterator

#include <ncell.tpp>

  } // end namespace utl

} // end namespace sico

#endif //__NCELL__
