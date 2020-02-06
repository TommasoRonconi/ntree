tests = [ 'ncell' ] # , 'ntree' ]

foreach _t : tests

exe = executable( 'test_' + _t + '.x',
                  [ 'test_' + _t + '.cpp' ],
                  include_directories : [ inc_ntree,
                                          inc_hilbert ],
                  dependencies : [ hilbert_dep,
                                   ntree_dep,
                                   utl_dep,
                                   gsl_dep ],
                  install : true,
                  install_dir : meson.current_source_dir() )

# test( _t + '_run_and_diff',
#       compare,
#       args : [ exe.full_path(),
#                _prefix + '/output/' + _t + '_ref.out' ],
#       workdir : meson.current_build_dir() )

endforeach
