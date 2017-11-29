#!/bin/sh

# Install a newer CMake
cd ~
CMAKE_PACKAGE=cmake-3.10.0-Linux-x86_64
wget "https://cmake.org/files/v3.10/"$CMAKE_PACKAGE".tar.gz"
tar xf $CMAKE_PACKAGE.tar.gz
mkdir cmake
cp -r $CMAKE_PACKAGE/* ./cmake/
cd -
