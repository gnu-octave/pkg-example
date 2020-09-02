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

```
>> pkg describe -verbose pkg-example
---
Package name:
        pkg-example
Version:
        1.0.0
Short description:
        A minimal example package for the GNU Octave package extensions.
Status:
        Not loaded
---
Provides:
Octave code
        hello_world
C++ code
        oct_demo
```

`news pkg-example`


## 3. Installing your package

You can install your package at any time into Octave with the command:

    pkg install https://github.com/gnu-octave/pkg-example/archive/master.zip


```
>> pkg install -verbose https://github.com/gnu-octave/pkg-example/archive/master.zip
mkdir (/tmp/oct-Fqa7Ib)
unzip (/tmp/oct-stScK7/master.zip, /tmp/oct-Fqa7Ib)
make: Entering directory '/tmp/oct-Fqa7Ib/pkg-example-master/src'
/usr/bin/mkoctfile-5.2.0 --verbose oct_demo.cc
g++ -c  -fPIC -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g -O2    oct_demo.cc -o /tmp/oct-CJ5EnW.o
g++ -I/usr/include/octave-5.2.0/octave/.. -I/usr/include/octave-5.2.0/octave  -pthread -fopenmp -g-O2 -shared -Wl,-Bsymbolic   -o oct_demo.oct  /tmp/oct-CJ5EnW.o
make: Leaving directory '/tmp/oct-Fqa7Ib/pkg-example-master/src'
copyfile /tmp/oct-Fqa7Ib/pkg-example-master/src/oct_demo.oct /tmp/oct-Fqa7Ib/pkg-example-master/inst/x86_64-pc-linux-gnu-api-v53
```
