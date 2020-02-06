#ifndef __HILBERT_C_INTERFACE__
#define __HILBERT_C_INTERFACE__

#include <stddef.h>

struct hcurve_c_handler {

  size_t dim;
  size_t depth;

  void * curve;

};

typedef struct hcurve_c_handler hilbert_curve_t;

#ifdef __cplusplus
extern "C" {
#endif

  

  hilbert_curve_t create_hilbert_curve_2d_8b ();

  void free_hilbert_curve_2d_8b ( hilbert_curve_t hc );

  unsigned long get_key_hcurve_2d_8b ( unsigned long * xx, hilbert_curve_t hc );

  void get_axes_hcurve_2d_8b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc );

  void get_grid_hcurve_2d_8b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc );

  

  hilbert_curve_t create_hilbert_curve_2d_16b ();

  void free_hilbert_curve_2d_16b ( hilbert_curve_t hc );

  unsigned long get_key_hcurve_2d_16b ( unsigned long * xx, hilbert_curve_t hc );

  void get_axes_hcurve_2d_16b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc );

  void get_grid_hcurve_2d_16b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc );

  

  hilbert_curve_t create_hilbert_curve_3d_8b ();

  void free_hilbert_curve_3d_8b ( hilbert_curve_t hc );

  unsigned long get_key_hcurve_3d_8b ( unsigned long * xx, hilbert_curve_t hc );

  void get_axes_hcurve_3d_8b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc );

  void get_grid_hcurve_3d_8b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc );

  
  
  hilbert_curve_t create_hilbert_curve_3d_16b ();

  void free_hilbert_curve_3d_16b ( hilbert_curve_t hc );

  unsigned long get_key_hcurve_3d_16b ( unsigned long * xx, hilbert_curve_t hc );

  void get_axes_hcurve_3d_16b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc );

  void get_grid_hcurve_3d_16b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc );
  
  
#ifdef __cplusplus
} // end extern "C"
#endif

#endif //__HILBERT_C_INTERFACE__
