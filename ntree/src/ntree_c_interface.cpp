#include <ntree_ds.h>
#include <ntree_c_interface.h>

extern "C" {

  // =======================================================================================  
  // ====================================== 2D 8 Bit =======================================
  // =======================================================================================

  ntree_t create_ntree_2d_8b ( double * coords, size_t ncoords, double boxmin, double boxmax ) {

    std::vector< double > coords_v { coords, coords + ncoords };
    return new sico::utl::ntree< 2, 8 >{ coords_v, boxmin, boxmax };

  }

  // =======================================================================================

  void free_ntree_2d_8b ( ntree_t tree ) {

    delete static_cast< sico::utl::ntree< 2, 8 > * >( tree );
    return;

  }

  // =======================================================================================

  nparticle_t find_key_ntree_2d_8b ( size_t key, ntree_t tree ) {

    auto ncell = static_cast< sico::utl::ntree< 2, 8 > * >( tree )->find( key );

    if ( *ncell ) 
      return nparticle_t{ ncell->particle->pos.data(), 2, ncell->particle->h_key };
    else 
      return nparticle_t{};
    
  }

  // =======================================================================================

  int_vector_t find_radius_ntree_2d_8b ( double * pos, double rad, ntree_t tree ) {

    std::vector< double > pos_v = { pos, pos + 2 };
    std::vector< size_t > keys_v = static_cast< sico::utl::ntree< 2, 8 > * >( tree )->find( pos_v,
											    rad );

    size_t size = keys_v.size();
    size_t * keys = new size_t[ size ];
    for ( size_t ii = 0; ii < size; ++ii ) keys[ ii ] = keys_v[ii];
    
    return int_vector_t{ keys, size };
    
  }

  // =======================================================================================  
  // ====================================== 2D 16 Bit ======================================
  // =======================================================================================

  ntree_t create_ntree_2d_16b ( double * coords, size_t ncoords, double boxmin, double boxmax ) {

    std::vector< double > coords_v { coords, coords + ncoords };
    return new sico::utl::ntree< 2, 16 >{ coords_v, boxmin, boxmax };

  }

  // =======================================================================================

  void free_ntree_2d_16b ( ntree_t tree ) {

    delete static_cast< sico::utl::ntree< 2, 16 > * >( tree );
    return;

  }

  // =======================================================================================

  nparticle_t find_key_ntree_2d_16b ( size_t key, ntree_t tree ) {

    auto ncell = static_cast< sico::utl::ntree< 2, 16 > * >( tree )->find( key );

    if ( *ncell ) 
      return nparticle_t{ ncell->particle->pos.data(), 2, ncell->particle->h_key };
    else 
      return nparticle_t{};
    
  }

  // =======================================================================================

  int_vector_t find_radius_ntree_2d_16b ( double * pos, double rad, ntree_t tree ) {

    std::vector< double > pos_v = { pos, pos + 2 };
    std::vector< size_t > keys_v = static_cast< sico::utl::ntree< 2, 16 > * >( tree )->find( pos_v,
											     rad );

    size_t size = keys_v.size();
    size_t * keys = new size_t[ size ];
    for ( size_t ii = 0; ii < size; ++ii ) keys[ ii ] = keys_v[ii];
    
    return int_vector_t{ keys, size };
    
  }

  // =======================================================================================  
  // ====================================== 3D 8 Bit =======================================
  // =======================================================================================

  ntree_t create_ntree_3d_8b ( double * coords, size_t ncoords, double boxmin, double boxmax ) {

    std::vector< double > coords_v { coords, coords + ncoords };
    return new sico::utl::ntree< 3, 8 >{ coords_v, boxmin, boxmax };

  }

  // =======================================================================================

  void free_ntree_3d_8b ( ntree_t tree ) {

    delete static_cast< sico::utl::ntree< 3, 8 > * >( tree );
    return;

  }

  // =======================================================================================

  nparticle_t find_key_ntree_3d_8b ( size_t key, ntree_t tree ) {

    auto ncell = static_cast< sico::utl::ntree< 3, 8 > * >( tree )->find( key );

    if ( *ncell ) 
      return nparticle_t{ ncell->particle->pos.data(), 3, ncell->particle->h_key };
    else 
      return nparticle_t{};
    
  }

  // =======================================================================================

  int_vector_t find_radius_ntree_3d_8b ( double * pos, double rad, ntree_t tree ) {

    std::vector< double > pos_v = { pos, pos + 3 };
    std::vector< size_t > keys_v = static_cast< sico::utl::ntree< 3, 8 > * >( tree )->find( pos_v,
											    rad );

    size_t size = keys_v.size();
    size_t * keys = new size_t[ size ];
    for ( size_t ii = 0; ii < size; ++ii ) keys[ ii ] = keys_v[ii];
    
    return int_vector_t{ keys, size };
    
  }

  // =======================================================================================  
  // ====================================== 3D 16 Bit ======================================
  // =======================================================================================

  ntree_t create_ntree_3d_16b ( double * coords, size_t ncoords, double boxmin, double boxmax ) {

    std::vector< double > coords_v { coords, coords + ncoords };
    return new sico::utl::ntree< 3, 16 >{ coords_v, boxmin, boxmax };

  }

  // =======================================================================================

  void free_ntree_3d_16b ( ntree_t tree ) {

    delete static_cast< sico::utl::ntree< 3, 16 > * >( tree );
    return;

  }

  // =======================================================================================

  nparticle_t find_key_ntree_3d_16b ( size_t key, ntree_t tree ) {

    auto ncell = static_cast< sico::utl::ntree< 3, 16 > * >( tree )->find( key );

    if ( *ncell ) 
      return nparticle_t{ ncell->particle->pos.data(), 3, ncell->particle->h_key };
    else 
      return nparticle_t{};
    
  }

  // =======================================================================================

  int_vector_t find_radius_ntree_3d_16b ( double * pos, double rad, ntree_t tree ) {

    std::vector< double > pos_v = { pos, pos + 3 };
    std::vector< size_t > keys_v = static_cast< sico::utl::ntree< 3, 16 > * >( tree )->find( pos_v,
											     rad );

    size_t size = keys_v.size();
    size_t * keys = new size_t[ size ];
    for ( size_t ii = 0; ii < size; ++ii ) keys[ ii ] = keys_v[ii];
    
    return int_vector_t{ keys, size };
    
  }
  
  // =======================================================================================  

} // end extern "C"
