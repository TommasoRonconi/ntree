#######################################################################
# Internal includes

inc_dir = 'include'

inc_hilbert = include_directories( inc_dir )

#######################################################################
# Hilbert Curve Template-Lib

hilbert_lib = library( 'hilbert',
                       [ 'src/hilbert_curve.cpp' ],
       	 	       include_directories : [ inc_hilbert ],
		       # dependencies : [ gsl_dep ],
                       install : true )

hilbert_dep = declare_dependency( link_with : hilbert_lib,
                                  include_directories : [ inc_hilbert ] )

lib_headers += [ root + '/hilbert_curve/' + inc_dir + '/hilbert_curve.h' ]

#######################################################################
# Cosmology Lib C interface

hilbert_c_lib = library( 'hilbert_c_wrap',
                         [ 'src/hilbert_c_interface.cpp' ],
                         include_directories : [ inc_hilbert ], #,
                                                 #inc_utl ],
                         dependencies : [ hilbert_dep ],
                         #                  gsl_dep,
                         #                  utl_dep,
                         #                  intrp_dep ],
                         install : true )

hilbert_c_dep = declare_dependency( link_with : hilbert_c_lib,
                                    include_directories : [ inc_hilbert ] )

hilbert_c_lib_name = hilbert_c_lib.full_path().split('/')[-1]

hilbert_c_path = '/'.join( [ get_option( 'prefix' ),
                             get_option( 'libdir' ),
                             hilbert_c_lib_name ] )

lib_headers += [ root + '/hilbert_curve/' + inc_dir + '/hilbert_c_interface.h' ]

#######################################################################
