# pkg-example

A minimal [package example](https://octave.org/doc/latest/Creating-Packages.html)
for [GNU Octave](https://www.octave.org).  Contained examples are:

- `hello_world.m`: Octave/Matlab code
- `fortran_demo.cc` / `fortran_my_ddot.f`: FORTRAN code
  ([BLAS DDOT](https://github.com/Reference-LAPACK/lapack/blob/master/BLAS/SRC/ddot.f))
  called by the oct-interface
- `oct_demo.cc`: C++ code called by the oct-interface
- `mex_demo.cc`: C code called by the mex-interface

This package serves as template.  Installing it is of little use.
In the following, we describe the Octave package development,
if you decide to host your package on GitHub.
Of course you can use this package template outside GitHub as well.

> We recommend **not to fork** this repository.
> You are probably not interested in upstream changes or pull request.
> Just copy the files from the ZIP-archive into your fresh repository
> or follow the guide below.

**Content:**

1. Setup your package repository
2. Change your package repository to your needs
3. Install your package
4. Publish your package


## 1. Setup your package repository

- Join the [GNU Octave GitHub organization](https://github.com/gnu-octave)
  by asking for invitation at our
  [Discourse forum](https://octave.discourse.group/t/github-gitlab-organization-for-gnu-octave/178).

- Being part of the GNU Octave GitHub organization, you can easily create
  a new repository by using this one as template repository.

  ![img](doc/create_repo_1.png)

  ![img](doc/create_repo_2.png)


## 2. Change your package repository to your needs

In this section we give a brief introduction to the files and folders of this
repository and Octave packages in general.  We do not use all features of
Octave packages.  For a more complete feature documentation, see
[the Octave manual](https://octave.org/doc/latest/Creating-Packages.html).
The following graphic gives an overview about what is installed
from this package repository.

![img](doc/directories.png)

On the left side of the graphic above is a clone of this repository.
On the right side the installed package in the default Octave package
installation location.

- [`COPYING`](COPYING): The license text of the package.  If you are not a
  specialist in software law, we recommend to use a well established software
  license.  See <https://spdx.org/licenses/> for examples.

- [`DESCRIPTION`](DESCRIPTION) and [`INDEX`](INDEX): As defined in
  [the Octave manual](https://octave.org/doc/latest/Creating-Packages.html).

- These three files are installed to a directory `packinfo` and tools like
  `pkg describe` use this information:

  ```
  >> pkg describe -verbose pkg-example
  ---
  Package name:
          pkg-example
  Version:
          1.0.0
  Short description:
          Minimal example package to demonstrate the Octave package  extensions.  It shows how to organize Octave, C/C++, and FORTRAN code within  a package and to properly compile it.
  Status:
          Not loaded
  ---
  Provides:
  Octave code
          hello_world
  C/C++/FORTRAN code
          mex_demo
          oct_demo
          fortran_demo
  ```

- `NEWS`: If this file is provided, the command `news pkg-example` prints it
  on the screen.

- [`doc`](doc): Optional folder.  All content is copied to the package
  installation directory.

- [`src`](src): **All source code** (Octave m-files, C/C++, and FORTRAN) goes
  here.

  - [`src/Makefile`](src/Makefile): during the package installation,
    `pkg install` will call `make` with its default target (not
    `make install`, etc.).  Thus specify here how to compile
    **C/C++ and FORTRAN** source code, see the example.

    > **Note:** Only `.m`, `.mex`, and `.oct` files are finally copied to the
    > package installation directory.


## 3. Install your package

You can always install the latest development version of your package,
for example the `master` branch, with the command:

    pkg install https://github.com/gnu-octave/pkg-example/archive/master.zip

or for a specific release, for example `1.0.0`, with the command:

    pkg install https://github.com/gnu-octave/pkg-example/archive/1.0.0.tar.gz

For Octave 5.2.0 the **verbose** output will look like this:

```
>> pkg install -verbose https://github.com/gnu-octave/pkg-example/archive/master.zip
mkdir (/tmp/oct-1zkcqo)
unzip (/tmp/oct-4WoyUf/master.zip, /tmp/oct-1zkcqo)
make: Entering directory '/tmp/oct-1zkcqo/pkg-example-master/src'

/usr/bin/mkoctfile-5.2.0 --verbose       oct_demo.cc
g++ -c  -fPIC -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g -O2    oct_demo.cc -o /tmp/oct-5tWsHS.o
g++ -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g -O2 -shared -Wl,-Bsymbolic   -o oct_demo.oct  /tmp/oct-5tWsHS.o

/usr/bin/mkoctfile-5.2.0 --verbose --mex mex_demo.c
gcc -c  -fPIC -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g -O2   -I.  -DMEX_DEBUG mex_demo.c -o /tmp/oct-K2WUDD.o
g++ -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g -O2 -shared -Wl,-Bsymbolic   -o mex_demo.mex  /tmp/oct-K2WUDD.o

/usr/bin/mkoctfile-5.2.0 --verbose       fortran_demo.cc fortran_my_ddot.f
gfortran -c -fPIC -g -O2 -std=legacy -fdefault-integer-8    fortran_my_ddot.f -o /tmp/oct-9riFAT.o
g++ -c  -fPIC -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g -O2    fortran_demo.cc -o /tmp/oct-NmFcVy.o
g++ -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g -O2 -shared -Wl,-Bsymbolic   -o fortran_demo.oct  /tmp/oct-9riFAT.o /tmp/oct-NmFcVy.o
make: Leaving directory '/tmp/oct-1zkcqo/pkg-example-master/src'

copyfile /tmp/oct-1zkcqo/pkg-example-master/src/hello_world.m /tmp/oct-1zkcqo/pkg-example-master/inst
copyfile /tmp/oct-1zkcqo/pkg-example-master/src/fortran_demo.oct /tmp/oct-1zkcqo/pkg-example-master/src/oct_demo.oct /tmp/oct-1zkcqo/pkg-example-master/src/mex_demo.mex /tmp/oct-1zkcqo/pkg-example-master/inst/x86_64-pc-linux-gnu-api-v53
warning: doc_cache_create: unusable help text found in file 'mex_demo'
```


## 4. Publish your package

> What is the use of your package, if only you know about it?

You have several options to gain attention, ordered by difficulty:

1. Announce your package at <https://octave.discourse.group/>.
2. Announce your package at <https://wiki.octave.org/Packages>.
3. Add your package to the
   [GNU Octave - Package extensions index](https://gnu-octave.github.io/pkg-index/).
4. Add your package to [Octave Forge](https://octave.sourceforge.io/packages.php)
   (notice that your package
   [must meet additional criteria](https://octave.sourceforge.io/developers.php)).
