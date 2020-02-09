#######################################################################
# Install python module

install_subdir( 'ntree', install_dir : 'python' )

#######################################################################
# Configure python module

conf_data = configuration_data()
conf_data.set( 'NTREE_WRAP_PATH', ntree_c_path )

configure_file( output : 'cwrap.py',
                input : 'cwrap.py.in',
                configuration : conf_data,
                install : true,
                install_dir : 'python/ntree/cwrap' )

#######################################################################
