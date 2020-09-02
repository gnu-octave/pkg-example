# pkg-example

A minimal example package for the GNU Octave package extensions.

This package serves as template.  Installing it is of little use.
In the following, we describe the GNU Octave package development,
if you decide to host your package on GitHub.
Of course you can use this package template outside GitHub as well.

> We recommend **not to fork** this repository.
> You are probably not interested in upstream changes or pull request.
> Just copy the files from the ZIP-archive into your fresh repository
> or follow the guide below.


## 1. Setup your repository

- Join the [GNU Octave GitHub organization](https://github.com/gnu-octave)
  by asking for invitation at our
  [Discourse forum](https://octave.discourse.group/t/github-gitlab-organization-for-gnu-octave/178).

- Being part of the GNU Octave GitHub organization, you can easily create
  a new repository by using this one as template repository.

  ![img](doc/create_repo_1.png)

  ![img](doc/create_repo_2.png)


## 2. Change your repository to your needs

In this section we give a brief introduction to the files and folders of this
repository and Octave packages in general.  We do not use all features of
Octave packages.  For a more complete feature documentation, see
[the Octave manual](https://octave.org/doc/latest/Creating-Packages.html).

### Necessary files in the root directory of your package

To give an impression what is installed from this package repository, see
the following graphic.

![img](doc/directories.png)

On the left side is a clone of this repository, and on the right side
the installed package in the default Octave package installation location.

- [`COPYING`](COPYING): The license text of the package.  If you are not a
  specialist in software law, we recommend to use a well established software
  license.  See <https://spdx.org/licenses/> for examples.

- [`DESCRIPTION`](DESCRIPTION) and [`INDEX`](INDEX): as defined in
  [the Octave manual](https://octave.org/doc/latest/Creating-Packages.html).

- These three files are stored in a directory `packinfo` and tools like
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

- If additionally a `NEWS` file is provided, the command `news pkg-example`
  prints them on the screen.

- [`doc`](doc): optional folder, all content is copied as is to the package
  installation directory.

- [`src`](src): **all source code** (Octave m-files, C/C++, and FORTRAN) goes
  here.

  - [`src/Makefile`](src/Makefile): during the package installation,
    `pkg install` will call `make` with its default target (no `make install`,
    etc.).  Thus specify here how to compile **C/C++ and FORTRAN** source
    code, see the example.

    > **Note:** Only `.m`, `.mex`, and `.oct` files are finally copied to the
    > package installation directory.


## 3. Installing your package

You can install your package at any time into Octave with the command:

    pkg install https://github.com/gnu-octave/pkg-example/archive/master.zip

or for a specific release with the command:

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
