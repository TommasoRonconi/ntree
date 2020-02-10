#ifndef __NTREE_C_INTERFACE__
#define __NTREE_C_INTERFACE__

#include <stddef.h>

struct nparticle_c_handler {

  double * coord;
  size_t size;
  size_t key;

} nparticle_default = { nullptr, 0, 0 };

typedef struct nparticle_c_handler nparticle_t;

struct int_vector_c_handler {

  size_t * vec;
  size_t size;
  
};

typedef struct int_vector_c_handler int_vector_t;

typedef void * ntree_t;

#ifdef __cplusplus
extern "C" {
#endif

  // =======================================================================================  

  ntree_t create_ntree_2d_8b ( double * coords, size_t ncoords, double boxmin, double boxmax );

  void free_ntree_2d_8b ( ntree_t tree );

  nparticle_t find_key_ntree_2d_8b ( size_t key, ntree_t tree );

  int_vector_t find_radius_ntree_2d_8b ( double * pos, double rad, ntree_t tree );

  // =======================================================================================  

  ntree_t create_ntree_2d_16b ( double * coords, size_t ncoords, double boxmin, double boxmax );

  void free_ntree_2d_16b ( ntree_t tree );

  nparticle_t find_key_ntree_2d_16b ( size_t key, ntree_t tree );

  int_vector_t find_radius_ntree_2d_16b ( double * pos, double rad, ntree_t tree );

  // =======================================================================================  

  ntree_t create_ntree_3d_8b ( double * coords, size_t ncoords, double boxmin, double boxmax );

  void free_ntree_3d_8b ( ntree_t tree );

  nparticle_t find_key_ntree_3d_8b ( size_t key, ntree_t tree );

  int_vector_t find_radius_ntree_3d_8b ( double * pos, double rad, ntree_t tree );

  // =======================================================================================  

  ntree_t create_ntree_3d_16b ( double * coords, size_t ncoords, double boxmin, double boxmax );

  void free_ntree_3d_16b ( ntree_t tree );

  nparticle_t find_key_ntree_3d_16b ( size_t key, ntree_t tree );

  int_vector_t find_radius_ntree_3d_16b ( double * pos, double rad, ntree_t tree );

  // =======================================================================================  
  
#ifdef __cplusplus
} // end extern "C"
#endif

#endif //__NTREE_C_INTERFACE__
