// fortran_demo.cc    -- example of a dynamically linked function for Octave.
// fortran_my_ddot.f  -- example FORTRAN code belonging to this example.
//
// To compile these files, type the command
//
//   mkoctfile fortran_demo.cc fortran_my_ddot.f
//
// from within Octave or from the shell prompt.  This will create a file
// called fortran_demo.oct that can be loaded by Octave.  To test the
// fortran_demo.oct file, start Octave and type the command
//
//   a = 1:5;
//   fortran_demo (a, 1, a, 1)  # a * a' == 55
//   fortran_demo (a, 2, a, 2)  # a(1:2:end) * a(1:2:end)' == 35
//
//
// Additional samples of code are in the examples directory of the Octave
// distribution.  See also the Octave manual
//
//   https://octave.org/doc/v5.2.0/External-Code-Interface.html
//
//
// Every user function should include <octave/oct.h> which imports the
// basic set of Octave header files required.  In particular this will define
// the DEFUN_DLD macro (defun-dld.h) which is used for every user function
// that is visible to Octave.  To properly define FORTRAN functions, the
// F77_FUNC macro is provided, too.

#include <octave/oct.h>

// To work with FORTRAN source code include <octave/f77-fcn.h> as well.
// This header file declares more useful macros for C++ code to ensure
// platform independence and compatibility with Octave.
//
//    F77_INT         Equivalent to Fortran INTEGER type
//    F77_INT4        Equivalent to Fortran INTEGER*4 type
//    F77_DBLE        Equivalent to Fortran DOUBLE PRECISION type
//    F77_REAL        Equivalent to Fortran REAL type
//    F77_CMPLX       Equivalent to Fortran COMPLEX type
//    F77_DBLE_CMPLX  Equivalent to Fortran DOUBLE COMPLEX type
//    F77_LOGICAL     Equivalent to Fortran LOGICAL type
//    F77_RET_T       Return type of a C++ function that acts like a Fortran
//                    subroutine.

#include <octave/f77-fcn.h>

// Before using a Fortran function from Octave's C++ oct-files, it is
// necessary to declare the Fortran function that should be called.  In this
// example the DDOT-function from BLAS the (Basic Linear Algrabra Subroutines),
// which computes the dot product for double vectors, should be called.
//
// As the symbol "DDOT" is already declared by Octave, the function was
// renamed to "MYDDOT".
//
//  DOUBLE PRECISION FUNCTION MYDDOT(N,DX,INCX,DY,INCY)
//
//  [in] N    is INTEGER  number of elements in input vector(s)
//  [in] DX   is DOUBLE PRECISION array, dimension ( 1 + ( N - 1 )*abs( INCX ) )
//  [in] INCX is INTEGER  storage spacing between elements of DX
//  [in] DY   is DOUBLE PRECISION array, dimension ( 1 + ( N - 1 )*abs( INCY ) )
//  [in] INCY is INTEGER  storage spacing between elements of DY
//
// All input parameters are [in] only, thus the inputs can be declared as
// "const" as they are not overwritten by the FORTRAN function.

extern "C"
{
  F77_DBLE
  F77_FUNC (myddot, MYDDOT)(const F77_INT&  /* N    */,
                            const F77_DBLE* /* DX   */,
                            const F77_INT&  /* INCX */,
                            const F77_DBLE* /* DY   */,
                            const F77_INT&  /* INCY */);
}

// The four arguments to the DEFUN_DLD macro are:
// 1) The function name as seen in Octave.
// 2) The variable to hold any inputs (of type octave_value_list)
// 3) The number of output arguments
// 4) A string to use as help text if 'help <function_name>' is entered.
//
// Note below that the third parameter (nargout) of DEFUN_DLD is not used.

DEFUN_DLD (fortran_demo, args, /* nargout */,
           "Fortran Demo help text.\n\
\n\
  r = fortran_demo (dx, incx, dy, incy)\n")
{
  if (args.length () != 4)
    print_usage ();

  NDArray x = args(0).array_value ();
  NDArray y = args(2).array_value ();
  double *DX = x.fortran_vec ();
  double *DY = y.fortran_vec ();

  // Determine and ensure same input vector length.
  F77_INT N = x.numel ();
  if (N != y.numel ())
    error ("fortran_demo: Vectors have different length.");

  F77_INT INCX = args(1).scalar_value ();
  F77_INT INCY = args(3).scalar_value ();

  return ovl (F77_FUNC (myddot, MYDDOT)(N, DX, INCX, DY, INCY));
}
