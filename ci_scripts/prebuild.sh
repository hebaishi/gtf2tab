#!/bin/sh
# Install a newer CMake
if [ "$TRAVIS_OS_NAME" = "linux" ]; then
  CMAKE_OS=Linux
else
  CMAKE_OS=Darwin
fi
cd ~
CMAKE_PACKAGE="cmake-3.10.0-"$CMAKE_OS"-x86_64"
wget "https://cmake.org/files/v3.10/"$CMAKE_PACKAGE".tar.gz"
tar xf $CMAKE_PACKAGE.tar.gz
mv $CMAKE_PACKAGE cmake
cd -
