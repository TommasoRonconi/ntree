import numpy
from .cwrap.cwrap import *

# ========================================================================================
# ========================================================================================
# ========================================================================================

# Wrap class ntree< dim, depth >:
class ntree () :
    """ Class to handle .
    
    [ ... ]
    
    Parameters
    ----------
    par : type
      [ ... ]
    """
    
    def __init__ ( self, coords, boxmin = 0., boxmax = 1., dim = 2, depth = 8 ) :
        """ Constructor of the class lin_interpolator
        """

        self.dim = dim
        self.depth = depth
        self.coords = ( c_double * len( coords ) )( *[ _c for _c in coords ] )

        if ( dim == 2 ) & ( depth == 8 ) :
            self.obj = lib_ntree.create_ntree_2d_8b( self.coords,
                                                     c_size_t( len( coords ) ),
                                                     c_double( boxmin ),
                                                     c_double( boxmax ) )
            self.free_obj = lib_ntree.free_ntree_2d_8b
            self.find_key = lib_ntree.find_key_ntree_2d_8b
            self.find_radius = lib_ntree.find_radius_ntree_2d_8b

        if ( dim == 2 ) & ( depth == 16 ) :
            self.obj = lib_ntree.create_ntree_2d_16b( self.coords,
                                                      c_size_t( len( coords ) ),
                                                      c_double( boxmin ),
                                                      c_double( boxmax ) )
            self.free_obj = lib_ntree.free_ntree_2d_16b
            self.find_key = lib_ntree.find_key_ntree_2d_16b
            self.find_radius = lib_ntree.find_radius_ntree_2d_16b

        if ( dim == 3 ) & ( depth == 8 ) :
            self.obj = lib_ntree.create_ntree_3d_8b( self.coords,
                                                     c_size_t( len( coords ) ),
                                                     c_double( boxmin ),
                                                     c_double( boxmax ) )
            self.free_obj = lib_ntree.free_ntree_3d_8b
            self.find_key = lib_ntree.find_key_ntree_3d_8b
            self.find_radius = lib_ntree.find_radius_ntree_3d_8b

        if ( dim == 3 ) & ( depth == 16 ) :
            self.obj = lib_ntree.create_ntree_3d_16b( self.coords,
                                                      c_size_t( len( coords ) ),
                                                      c_double( boxmin ),
                                                      c_double( boxmax ) )
            self.free_obj = lib_ntree.free_ntree_3d_16b
            self.find_key = lib_ntree.find_key_ntree_3d_16b
            self.find_radius = lib_ntree.find_radius_ntree_3d_16b


    def __del__ ( self ) :
        """ Destructor of the class ntree< dim, depth >
        """

        # Python call to lin_interpolator dtor:
        self.free_obj( self.obj )

        return


    def __getitem__ ( self, kk ) :
        """ array subscript operator ( accessing ) 
        """

        return self.find_key( c_size_t( kk ), self.obj )

    # def __setitem__ ( self, kk ) :
    #     """ array subscript operator ( setting ) 
    #     """

    #     return 

    def query_radius ( self, pos, rad ) :
        """ find list of keys rad-far from pos
        """

        pp = ( c_double * len( pos ) )( *[ numpy.float64( _p ) for _p in pos  ] )
        _output = self.find_radius( pp, c_double( rad ), self.obj )

        if _output.size > 0 :
            keys = ( c_size_t * _output.size )( *[ _output.vec[ ii ]
                                                   for ii in range( _output.size ) ] )
            return numpy.array( keys, dtype = c_size_t )
        else :
            return numpy.array( [], dtype = c_size_t )

    
