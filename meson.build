#######################################################################
# Global project info

project( 'master',
         'cpp',
         default_options : [ 'cpp_std=c++17',
                             # 'b_sanitize=address',
                             'buildtype=debugoptimized',
                             'prefix=' + meson.source_root() + '/install',
                             'libdir=lib' ],
         version : '0.1',
         license : 'SISSA' )

root = meson.source_root()

cxx = meson.get_compiler( 'cpp' )

cxx_args = [ '-Wall',
             '-Wextra',
             '-fopenmp' ]

foreach cxx_arg : cxx_args
if cxx.has_argument( cxx_arg ) 
add_global_arguments( cxx_arg,
                      language : 'cpp' )
endif
endforeach

#######################################################################
# External dependencies

# OMP

omp_dep = dependency( 'openmp',
                      required : true )

# GSL

gsl_dep = dependency( 'gsl',
                      required : true,
                      version : '>=2' )

# FFTLog

# fftlog_dep = dependency( 'fftlog',
#                          required : true )

#######################################################################
# Internal includes

lib_headers = []

#######################################################################
# Utilities Lib

subdir( 'utilities' )

#######################################################################
# Interpolation Lib

# subdir( 'interpolator' )

#######################################################################
# Hilbert-Curve Lib

subdir( 'hilbert_curve' )

#######################################################################
# N-Treee Lib

subdir( 'ntree' )

#######################################################################
# Further installation commands

install_headers( lib_headers )

#######################################################################
# Python wrap

subdir( 'python' )

#######################################################################
# Testing

subdir( 'tests' )
