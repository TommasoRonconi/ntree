#ifndef __NTREE_C_INTERFACE__
#define __NTREE_C_INTERFACE__

#include <stddef.h>

// struct hcurve_c_handler {

//   size_t dim;
//   size_t depth;

//   void * curve;

// };

// typedef struct hcurve_c_handler hilbert_curve_t;
typedef void * ntree_t;

#ifdef __cplusplus
extern "C" {
#endif

  ntree_t create_ntree_2d_8b ( double * coords, double boxmin, double boxmax );

  void free_ntree_2d_8b ( ntree_t tree );  
  
#ifdef __cplusplus
} // end extern "C"
#endif

#endif //__NTREE_C_INTERFACE__
