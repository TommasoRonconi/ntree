#######################################################################
# Internal includes

inc_dir = 'include'

inc_ntree = include_directories( inc_dir )

#######################################################################
# N-Tree Template-Lib

ntree_lib = library( 'ntree',
                     [ 'src/ncell.cpp',
                       'src/ntree_ds.cpp' ],
       	 	     include_directories : [ inc_ntree,
                                             inc_hilbert,
                                             inc_utl ],
		     dependencies : [ hilbert_dep,
                                      utl_dep,
                                      omp_dep,
                                      gsl_dep ],
                     install : true )

ntree_dep = declare_dependency( link_with : ntree_lib,
                                include_directories : [ inc_ntree,
                                                        inc_hilbert,
                                                        inc_utl ] )

lib_headers += [ root + '/ntree/' + inc_dir + '/ncell.h',
                 root + '/ntree/' + inc_dir + '/ntree_ds.h',
                 root + '/ntree/' + inc_dir + '/ncell.tpp',
                 root + '/ntree/' + inc_dir + '/ntree_ds.tpp' ]

#######################################################################
# N-Tree Lib C interface

# ntree_c_lib = library( 'ntree_c_wrap',
#                        [ 'src/ntree_c_interface.cpp' ],
#                        include_directories : [ inc_ntree ], #,
#                        #inc_utl ],
#                        dependencies : [ ntree_dep ],
#                        #                  gsl_dep,
#                        #                  utl_dep,
#                        #                  intrp_dep ],
#                        install : true )

# ntree_c_dep = declare_dependency( link_with : ntree_c_lib,
#                                   include_directories : [ inc_ntree ] )

# ntree_c_lib_name = ntree_c_lib.full_path().split('/')[-1]

# ntree_c_path = '/'.join( [ get_option( 'prefix' ),
#                            get_option( 'libdir' ),
#                            ntree_c_lib_name ] )

# lib_headers += [ root + '/ntree/' + inc_dir + '/ntree_c_interface.h' ]

#######################################################################
