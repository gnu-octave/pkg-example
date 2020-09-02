# This is an example Makefile for a GNU Octave package.
#
# It tells the Octave "pkg" tool how to compile the contained source files.
#
# More complex setups, including "./configure" script are possible too.
# Please read the Octave manual for more information.
#
#     https://octave.org/doc/latest/Creating-Packages.html
#

all:
	$(MKOCTFILE)       oct_demo.cc
	$(MKOCTFILE) --mex mex_demo.c
	$(MKOCTFILE)       fortran_demo.cc fortran_my_ddot.f
