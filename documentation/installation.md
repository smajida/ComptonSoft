Installation | Compton Soft
================================================================

[Home](../README.md)

 1. Platforms
----------------------------------------------------------------

- Mac: the author's standard environment
- Linux

----

 2. Required software
----------------------------------------------------------------

### (1) C++ compliler

### (2) [CMake](http://www.cmake.org/) (Cross platform make)
*version 3.0.7 or later*

For easy installation, this package uses CMake to generate building tools such
as Makefile.

### (3) [Boost C++ library](http://www.boost.org/)
*version 1.56.0 or later*

### (4) [ANL Next framework](http://www.astro.isas.jaxa.jp/~odaka/anlnext/)
*version 1.7.0 or later*

Compton Soft uses the ANL Next framework. ANL Next is a framework for
constructing software that performs event-by-event analysis, which usually
appears in data processing or analysis of radiation detectors.

ANL Next requires following libraries:

- Boost C++ library
- Ruby
- SWIG

You can find
[installation guide](https://github.com/odakahirokazu/ANLNext#readme)
of ANL Next.

### (5) [Geant4](http://geant4.cern.ch/)
*version 10.0 or later*

A toolkit library for Monte Carlo simulations.
Following building options are required:

- "global" libraries
- shared libraries
- install all header files in one directory
- GDML and visualization options are recommended.

Example of running cmake:

    unix> cmake \
      -DCMAKE_INSTALL_PREFIX=../geant4.10.01.p02-install \
      -DGEANT4_USE_GDML=ON \
      -DGEANT4_USE_QT=ON \
      -DGEANT4_USE_OPENGL_X11=ON \
      -DGEANT4_USE_RAYTRACER_X11=ON \
      -DGEANT4_USE_NETWORKDAWN=ON \
      ../geant4.10.01.p02

### (6) [ROOT](http://root.cern.ch/)
*version 5.34.05 or later*

A data analysis framework.


 3. Installation
----------------------------------------------------------------

### (1) Obtain Compton Soft via GitHub.

    unix> git clone https://github.com/odakahirokazu/ComptonSoft.git

### (2) Perform CMake.

Make a directory for building the software, and then move to the directory.

    unix> cd ComptonSoft
    unix> mkdir build
    unix> cd build

Perform cmake to generate Makefiles. Give the directory of the source tree to
`cmake` command.

    unix> cmake .. [options] -DCMAKE_INSTALL_PREFIX=/path/to/install

There are several options:

#### User interface options
- `CS_USE_RUBY`    (Default=ON):  enable Ruby binding.
- `CS_USE_EXE`     (Default=OFF): create standalone executables.

#### library options
- `CS_USE_GDML`    (Default=ON): enable GDML.
- `CS_USE_SIMX`    (Default=OFF): enable SimX interface.
- `CS_USE_VIS`     (Default=OFF): enable OpenGL visualization of Geant4.
- `CS_USE_VIS_QT`  (Default=ON): enable Qt visualization of Geant4.

#### install options
- `CS_INSTALL_HEADERS` (Default=ON): install all header files.
- `CS_INSTALL_CMAKE_FILES` (Default=ON): install all cmake files.

By default, the install destination is set to `${HOME}`. So `make install` will
install headers and libraries into the user's home directory, such as
`${HOME}/include` or `${HOME}/lib`. You can change it by setting
`CMAKE_INSTALL_PREFIX`.

This is an example to turn off GDML and Qt-visualization for Geant4:

    unix> cmake .. \
      -DCS_USE_GDML=OFF \
      -DCS_USE_VIS_QT=OFF \
      -DCMAKE_INSTALL_PREFIX=/path/to/install

### (3) Make and install

    unix> make
    unix> make install

NOTE: you can use `make -jN` (N: number of parallel complilation processes)
instead of `make` for faster build.

****************************************************************
