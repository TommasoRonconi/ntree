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
    
    def __init__ ( self, dim = 2, depth = 16 ) :
        """ Constructor of the class lin_interpolator
        """

        self.dim = dim
        self.depth = depth

        if ( dim == 2 ) & ( depth == 8 ) :
            self.obj = lib_ntree.create_ntree_2d_8b()
            self.free_obj = lib_ntree.free_ntree_2d_8b


    def __del__ ( self ) :
        """ Destructor of the class ntree< dim, depth >
        """

        # Python call to lin_interpolator dtor:
        self.free_obj( self.obj )
