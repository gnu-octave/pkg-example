// mex_demo.c -- example of a dynamically linked function for Octave.
//
// To compile this file, type the command
//
//   mkoctfile --mex mex_demo.c
//
// from within Octave or from the shell prompt.  This will create a file
// called mex_demo.mex that can be loaded by Octave.  To test the mex_demo.mex
// file, start Octave and type the command
//
// d = mex_demo ("easy as", 1, 2, 3)
//
// at the Octave prompt.  Octave should respond by printing
//
//   Hello, world!
//   I have 4 inputs and 1 output
//   d =  1.2346
//
// Additional samples of code are in the examples directory of the Octave
// distribution.  See also the Octave manual
//
//   https://octave.org/doc/v5.2.0/External-Code-Interface.html

#include "mex.h"

// Every user function should include "mex.h" which imports the basic set of
// function prototypes necessary for dynamically linked functions.  In
// particular, it will declare mexFunction which is used by every function
// which will be visible to Octave.  A mexFunction is visible in Octave under
// the name of the source code file without the extension.
//
// The four arguments to mexFunction are:
// 1) The number of return arguments (# of left-hand side args).
// 2) An array of pointers to return arguments.
// 3) The number of input arguments (# of right-hand side args).
// 4) An array of pointers to input arguments.

void
mexFunction (int nlhs, mxArray *plhs[],
             int nrhs, const mxArray *prhs[])
{
  mexPrintf ("Hello, World!\n");

  mexPrintf ("I have %d inputs and %d outputs\n", nrhs, nlhs);

  // Demonstrate returning a matrix with a double value
  mxArray *v = mxCreateDoubleMatrix (1, 1, mxREAL);
  double *data = mxGetPr (v);
  *data = 1.23456789;
  plhs[0] = v;

  // Return empty matrices for any other outputs
  for (int i = 1; i < nlhs; i++)
    plhs[i] = mxCreateDoubleMatrix (0, 0, mxREAL);
}
