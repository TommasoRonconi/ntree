#include <ntree_ds.h>
#include <ntree_c_interface.h>

extern "C" {

  // =======================================================================================

  ntree_t create_ntree_2d_8b ( double * coords, double boxmin, double boxmax ) {

    std::vector< double > coords_v { coords, coords + 2 };
    return new sico::utl::ntree< 2, 8 >{ coords_v, boxmin, boxmax };

  }

  // =======================================================================================

  void free_ntree_2d_8b ( ntree_t tree ) {

    delete static_cast< sico::utl::ntree< 2, 8 > * >( tree );
    return;

  }

  // =======================================================================================  

} // end extern "C"
