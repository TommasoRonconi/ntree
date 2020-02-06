#ifndef __NTREE__
#define __NTREE__

#include <memory>

// #include <bit_manipulator.h>
// #include <hilbert_curve.h>
#include <ncell.h>

namespace sico {

  namespace utl {

    template < const size_t dim = 2 >
    class ntree {

      std::unique_ptr< ncell< dim > > root = nullptr;

    public:

      ntree () = default;

      ~ntree () = default;

      // iterator begin() { return root->leftmost(); }

      // iterator end() { return iterator{ nullptr }; }

      void clear () { root.reset(); return; }

      // iterator find ( const size_t key ) {

      // 	return iterator{ root->find( key ) };

      // }

    }; // endclass ntree

  } // endnamespace utl
  
} // endnamespace sico

#include <ntree_ds.tpp>

#endif //__NTREE__
