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

      hilbert_coord_t< dim, depth > h_coord {};
      
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
      	  throw sico_err::size_invalid( "Miss-matching dimension between template value " +
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

      std::vector< std::size_t > _cell_min = std::vector< std::size_t>( dim );
      std::vector< std::size_t > _cell_max = std::vector< std::size_t>( dim );

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

      void set_limits ( const std::size_t keyloc,
			const hilbert_curve< dim, depth > & hloc );

      // clears up everything from the current cell and below
      void clear ();

      // inserts into vector keys, all the particle keys within cell
      void dump_all ( std::vector< std::size_t > & keys );

      // starting from the current cell gets you to the
      // first occupied one, following the hilbert ordering
      ncell * leftmost ();

      // starting from the current cell gets you to the
      // last occupied one, following the hilbert ordering
      ncell * rightmost ();

      ncell * find ( const size_t key );

      // starting from a known cell gets you to the previous occupied one
      // (Warning: this might mess-up stuff if the key is not selected accurately,
      //           no error nor exception is raised independently of the key provided
      //           but behaviour is undefined in case the key is not within the range)
      ncell * find_prev ( const size_t key );

      // starting from a known cell gets you to the next occupied one
      // (Warning: this might mess-up stuff if the key is not selected accurately,
      //           no error nor exception is raised independently of the key provided
      //           but behaviour is undefined in case the key is not within the range)
      ncell * find_next ( const size_t key );

      // recursively searches for keys included in a range:
      // starting from the current cell:
      // - decomposes space into sub-cells;
      // - finds those that are included within ranges;
      // - appends keys to output vector;
      void find_in_range ( const std::vector< unsigned int > minima,
			   const std::vector< unsigned int > maxima,
			   std::vector< std::size_t > & keys );

      // template
      class iterator {

	ncell * current;

      public:

	iterator () noexcept = default;

	iterator ( ncell * cl ) : current{ cl } {}

	~iterator () noexcept = default;

	ncell * operator*() { return current; }
      
	ncell * operator->() const { return current;  }

	iterator & operator++ () {

	  current = current->find_next( current->particle->h_key );

	  return *this;

	}
  
	/**
	 *  @brief Logical-equality operator overload
	 *
	 *  @param other the r-value to be compared
	 *
	 *  @return bool, true if the two iterator contain the same pointer, false if not
	 */
	bool operator==( const iterator& other ) { return current == other.current; }
  
	/**
	 *  @brief Logical-inequality operator overload
	 *
	 *  @param other the r-value to be compared
	 *
	 *  @return Implementation is done in terms of overloaded equality operator
	 */
	bool operator!=( const iterator& other ) { return !( *this == other ); }

      }; // endclass iterator

    }; // endclass ncell

#include <ncell.tpp>

  } // end namespace utl

} // end namespace sico

#endif //__NCELL__
