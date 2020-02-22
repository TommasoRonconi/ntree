tests = [ 'ncell',
          'ntree_ds',
          'ntree_dimVSdepth',
          'find_radius_performances',
          'ncell_set_limits' ]

foreach _t : tests

exe = executable( 'test_' + _t + '.x',
                  [ 'test_' + _t + '.cpp' ],
                  include_directories : [ inc_ntree,
                                          inc_hilbert ],
                  dependencies : [ hilbert_dep,
                                   ntree_dep,
                                   utl_dep,
                                   omp_dep,
                                   gsl_dep ],
                  install : false )

# test( _t + '_run_and_diff',
#       compare,
#       args : [ exe.full_path(),
#                _prefix + '/output/' + _t + '_ref.out' ],
#       workdir : meson.current_build_dir() )

endforeach
