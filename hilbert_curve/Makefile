##############################################################
######################### Makefile ###########################
##############################################################

SHELL = /bin/bash

##############################################################
# Optional flags, uncomment to activate:

# OPT +=

##############################################################
# Variables and flags:

CXXC = g++
MPIC = mpicc

EX = x

EO = o

ESO = so

dirR = $(PWD)
dirI = $(dirR)/include
dirS = $(dirR)/src
dirL = $(dirR)/lib
dirO = $(dirR)/obj
dirD = $(dirR)/Doxygen

FLAGS = -O3 -std=c++17 # -O1 -g -ggdb -fsanitize=address

C_FLAGS = $(FLAGS) -I $(dirI) -I./../utilities/include -O3 -Wall -Wextra -fopenmp
LD_FLAGS = $(FLAGS) -Wl,-rpath,$(dirL) -L $(dirL)

##############################################################
# Libraries:

LIB_GSL = /opt/gsl/gsl2.5
# LIB_FFTLOG = /opt/fftlog

C_FLAGS += -I $(LIB_GSL)/include
LD_FLAGS += -L $(LIB_GSL)/lib -lgsl -lgslcblas -lm #-L $(LIB_FFTLOG)/lib -lfftlog -lm

##############################################################
# Objects:

OBJ_hilbert_curve = $(dirO)/hilbert_curve.$(EO)

##############################################################
# Shared-Objects:

lib_hilbert_curve = $(dirL)/libhilbertcurve.$(ESO)

##############################################################
# Rules:

# default rule

all: Makefile $(dirO) $(dirL) $(lib_hilbert_curve)

# make output-directories

$(dirO):
	mkdir -p $@

$(dirL):
	mkdir -p $@

# general rule to compile objects

$(dirO)/%.$(EO): $(dirS)/%.cpp
	$(CXXC) $(C_FLAGS) -o $@ -fPIC -c $<

# rules to compile shared-objects

$(lib_hilbert_curve): $(OBJ_hilbert_curve)
	$(CXXC) $(LD_FLAGS) -shared -o $@ $^

# make the documentation

documentation: $(dirD)/doxy.in
	doxygen $^

# eliminate default suffixes

.SUFFIXES:
SUFFIXES =

# just consider our own suffixes

.SUFFIXES: .h .cpp .tpp .$(EO) .$(ESO)

##############################################################
# Pre-requisites:

$(dirO)/hilbert_curve.$(EO): $(dirI)/hilbert_curve.h

##############################################################
# phony rules

.PHONY: clean clean_doc

clean:
	$(info clean up)
	rm -rf *~ *# $(dirS)/*~ $(dirI)/*~ $(dirD)/*~ $(dirO) $(dirL)

clean_doc:
	$(info clean doc)
	rm -rf  $(dirD)/*~ $(dirD)/html $(dirD)/latex

clean_all: clean clean_doc


