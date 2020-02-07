#ifndef __NTREE__
#define __NTREE__

#include <memory>
#include <string>

// #include <bit_manipulator.h>
#include <error_handling.h>
#include <hilbert_curve.h>
#include <ncell.h>

namespace sico {

  namespace utl {

    template < const size_t dim = 2, const size_t depth = 2 >
    class ntree {

      // private members regulating the geometry of space:
      const double _boxmin;
      const double _boxmax;
      const double _lenght;
      const double _expand;
      
      std::unique_ptr< ncell< dim, depth > > root = nullptr;

    public:

      ntree () = default;

      // coordinates vector should have size = dim * n_objs
      // iterate over it with [ ii * dim + jj ] indexing
      ntree ( const std::vector< double > & coords,
	      const double & boxmin = 0.,
	      const double & boxmax = 1. );

      ~ntree () = default;

      // iterator begin() { return root->leftmost(); }

      // iterator end() { return iterator{ nullptr }; }

      void clear () { root.reset(); return; }

      // iterator find ( const size_t key ) {

      // 	return iterator{ root->find( key ) };

      // }

    }; // endclass ntree

#include <ntree_ds.tpp>
    
  } // endnamespace utl
  
} // endnamespace sico

#endif //__NTREE__
