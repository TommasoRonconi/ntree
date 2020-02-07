#ifndef __NCELL__
#define __NCELL__

#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>

// #include <error_handling.h>
#include <bit_manipulator.h>
#include <hilbert_curve.h>

namespace sico {

  namespace utl {

    template < const size_t dim = 2 >
    struct nparticle {

      std::vector< size_t > coord = std::vector< size_t >( dim );

      size_t h_key;

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

      std::unique_ptr< nparticle< dim > > particle = nullptr;

      //public:

      // this serves as default constructor:
      ncell ( std::size_t level = 0, ncell * parent = nullptr )
	: _level{ level }, _parent { parent } {}

      ncell ( nparticle< dim > * new_particle, std::size_t level = 0, ncell * parent = nullptr )
	: _level{ level }, _parent { parent } {

	  particle.reset( new_particle );
    
	}

      ~ncell() noexcept = default;

      // to implement this, need to overload operator- in class iterator:
      // size_t size () { return end() - begin(); }
  
      void insert ( const std::vector< nparticle< dim > * > & parts );

      short hash_func ( const size_t key ) {

	return bits( key, dim * ( depth - _level - 1 ), dim );
	// return bits( key, dim * ( _level - 1 ), dim );

      }

      void clear ();

      ncell * find ( const size_t key );

      ncell * find_next ( const size_t key );

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
