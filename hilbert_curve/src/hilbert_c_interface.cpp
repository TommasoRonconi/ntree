#include <hilbert_c_interface.h>
#include <hilbert_curve.h>

extern "C" {

  // =======================================================================================

  hilbert_curve_t create_hilbert_curve_2d_8b () {

    return hilbert_curve_t{ 2, 8, new hilbert_curve< 2, 8 > {} };

  }

  // =======================================================================================

  void free_hilbert_curve_2d_8b ( hilbert_curve_t hc ) {

    delete static_cast< hilbert_curve< 2, 8 > * >( hc.curve );
    return;

  }

  // =======================================================================================  

  unsigned long get_key_hcurve_2d_8b ( unsigned long * xx, hilbert_curve_t hc ) {

    return static_cast< hilbert_curve< 2, 8 > * >( hc.curve )->get_key( hilbert_coord_t< 2, 8 >{ xx[ 0 ], xx[ 1 ] } ).to_ulong();

  }  
  
  // =======================================================================================  

  void get_axes_hcurve_2d_8b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc ) {

    hilbert_coord_t< 2, 8 > axes_v =
      static_cast< hilbert_curve< 2, 8 > * >( hc.curve )->get_axes( hilbert_coord_t< 2, 8 >{ xx[ 0 ], xx[ 1 ] } );
    axes[ 0 ] = axes_v[ 0 ].to_ulong();
    axes[ 1 ] = axes_v[ 1 ].to_ulong();

    return;

  }  

  // =======================================================================================  

  void get_grid_hcurve_2d_8b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc ) {

    hilbert_coord_t< 2, 8 > grid_v =
      static_cast< hilbert_curve< 2, 8 > * >( hc.curve )->get_grid( hilbert_coord_t< 2, 8 >{ xx[ 0 ], xx[ 1 ] } );
    grid[ 0 ] = grid_v[ 0 ].to_ulong();
    grid[ 1 ] = grid_v[ 1 ].to_ulong();

    return;

  }  

  // =======================================================================================  
  // =======================================================================================
  // =======================================================================================

  // =======================================================================================

  hilbert_curve_t create_hilbert_curve_2d_16b () {

    return hilbert_curve_t{ 2, 16, new hilbert_curve< 2, 16 > {} };

  }

  // =======================================================================================

  void free_hilbert_curve_2d_16b ( hilbert_curve_t hc ) {

    delete static_cast< hilbert_curve< 2, 16 > * >( hc.curve );
    return;

  }

  // =======================================================================================  

  unsigned long get_key_hcurve_2d_16b ( unsigned long * xx, hilbert_curve_t hc ) {

    return static_cast< hilbert_curve< 2, 16 > * >( hc.curve )->get_key( hilbert_coord_t< 2, 16 >{ xx[ 0 ], xx[ 1 ] } ).to_ulong();

  }  
  
  // =======================================================================================  

  void get_axes_hcurve_2d_16b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc ) {

    hilbert_coord_t< 2, 16 > axes_v =
      static_cast< hilbert_curve< 2, 16 > * >( hc.curve )->get_axes( hilbert_coord_t< 2, 16 >{ xx[ 0 ], xx[ 1 ] } );
    axes[ 0 ] = axes_v[ 0 ].to_ulong();
    axes[ 1 ] = axes_v[ 1 ].to_ulong();

    return;

  }  

  // =======================================================================================  

  void get_grid_hcurve_2d_16b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc ) {

    hilbert_coord_t< 2, 16 > grid_v =
      static_cast< hilbert_curve< 2, 16 > * >( hc.curve )->get_grid( hilbert_coord_t< 2, 16 >{ xx[ 0 ], xx[ 1 ] } );
    grid[ 0 ] = grid_v[ 0 ].to_ulong();
    grid[ 1 ] = grid_v[ 1 ].to_ulong();

    return;

  }  

  // =======================================================================================  
  // =======================================================================================
  // =======================================================================================

  hilbert_curve_t create_hilbert_curve_3d_8b () {

    return hilbert_curve_t{ 3, 8, new hilbert_curve< 3, 8 > {} };

  }

  // =======================================================================================

  void free_hilbert_curve_3d_8b ( hilbert_curve_t hc ) {

    delete static_cast< hilbert_curve< 3, 8 > * >( hc.curve );
    return;

  }

  // =======================================================================================  

  unsigned long get_key_hcurve_3d_8b ( unsigned long * xx, hilbert_curve_t hc ) {

    return static_cast< hilbert_curve< 3, 8 > * >( hc.curve )->get_key( hilbert_coord_t< 3, 8 >{ xx[ 0 ], xx[ 1 ], xx[ 2 ] } ).to_ulong();

  }  
  
  // =======================================================================================  

  void get_axes_hcurve_3d_8b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc ) {

    hilbert_coord_t< 3, 8 > axes_v =
      static_cast< hilbert_curve< 3, 8 > * >( hc.curve )->get_axes( hilbert_coord_t< 3, 8 >{ xx[ 0 ], xx[ 1 ], xx[ 2 ] } );
    axes[ 0 ] = axes_v( 0 );
    axes[ 1 ] = axes_v( 1 );
    axes[ 2 ] = axes_v( 2 );

    return;

  }  

  // =======================================================================================  

  void get_grid_hcurve_3d_8b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc ) {

    hilbert_coord_t< 3, 8 > coord = { xx[ 0 ], xx[ 1 ], xx[ 2 ] };
    
    hilbert_coord_t< 3, 8 > grid_v =
      static_cast< hilbert_curve< 3, 8 > * >( hc.curve )->get_grid( coord );
    grid[ 0 ] = grid_v( 0 );
    grid[ 1 ] = grid_v( 1 );
    grid[ 2 ] = grid_v( 2 );

    return;

  }  

  // =======================================================================================  
  // =======================================================================================
  // =======================================================================================

  hilbert_curve_t create_hilbert_curve_3d_16b () {

    return hilbert_curve_t{ 3, 16, new hilbert_curve< 3, 16 > {} };

  }

  // =======================================================================================

  void free_hilbert_curve_3d_16b ( hilbert_curve_t hc ) {

    delete static_cast< hilbert_curve< 3, 16 > * >( hc.curve );
    return;

  }

  // =======================================================================================  

  unsigned long get_key_hcurve_3d_16b ( unsigned long * xx, hilbert_curve_t hc ) {

    return static_cast< hilbert_curve< 3, 16 > * >( hc.curve )->get_key( hilbert_coord_t< 3, 16 >{ xx[ 0 ], xx[ 1 ], xx[ 2 ] } ).to_ulong();

  }  
  
  // =======================================================================================  

  void get_axes_hcurve_3d_16b ( unsigned long * xx, unsigned long * axes, hilbert_curve_t hc ) {

    hilbert_coord_t< 3, 16 > axes_v =
      static_cast< hilbert_curve< 3, 16 > * >( hc.curve )->get_axes( hilbert_coord_t< 3, 16 >{ xx[ 0 ], xx[ 1 ], xx[ 2 ] } );
    axes[ 0 ] = axes_v( 0 );
    axes[ 1 ] = axes_v( 1 );
    axes[ 2 ] = axes_v( 2 );

    return;

  }  

  // =======================================================================================  

  void get_grid_hcurve_3d_16b ( unsigned long * xx, unsigned long * grid, hilbert_curve_t hc ) {

    hilbert_coord_t< 3, 16 > coord = { xx[ 0 ], xx[ 1 ], xx[ 2 ] };
    
    hilbert_coord_t< 3, 16 > grid_v =
      static_cast< hilbert_curve< 3, 16 > * >( hc.curve )->get_grid( coord );
    grid[ 0 ] = grid_v( 0 );
    grid[ 1 ] = grid_v( 1 );
    grid[ 2 ] = grid_v( 2 );

    return;

  }  

  // =======================================================================================  

} // end extern "C"
  
