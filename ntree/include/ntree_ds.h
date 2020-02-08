#ifndef __NTREE__
#define __NTREE__

#include <memory>
#include <string>
#include <initializer_list>

// #include <bit_manipulator.h>
#include <error_handling.h>
#include <hilbert_curve.h>
#include <ncell.h>

namespace sico {

  namespace utl {

    template < const size_t dim = 2, const size_t depth = 2 >
    class ntree {

      // private members regulating the geometry of space:
      double _boxmin = 0.;
      double _boxmax = 1.;
      double _lenght = 1.;
      double _expand = 1.;
      std::size_t _size = 0;
      hilbert_curve< dim, depth > _hc {};
      
      std::unique_ptr< ncell< dim, depth > > root = nullptr;

    public:

      ntree () = default;

      // coordinates vector should have size = dim * n_objs
      // iterate over it with [ ii * dim + jj ] indexing
      ntree ( const std::vector< double > & coords,
	      const double & boxmin = 0.,
	      const double & boxmax = 1. );

      ~ntree () = default;

      typename ncell< dim, depth >::iterator begin() { return root->leftmost(); }

      typename ncell< dim, depth >::iterator end() {
	
	return typename ncell< dim, depth >::iterator{ nullptr };
	
      }

      void clear () { root.reset(); return; }
      
      typename ncell< dim, depth >::iterator find ( const size_t key ) {

      	return typename ncell< dim, depth >::iterator{ root->find( key ) };

      }

    }; // endclass ntree

#include <ntree_ds.tpp>
    
  } // endnamespace utl
  
} // endnamespace sico

#endif //__NTREE__
