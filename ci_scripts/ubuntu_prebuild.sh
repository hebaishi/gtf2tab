#!/bin/sh

# Remove the current version of CMake
sudo apt-get purge -y cmake

# Install a newer CMake
cd /tmp
CMAKE_PACKAGE=cmake-3.10.0-Linux-x86_64
wget "https://cmake.org/files/v3.10/"$CMAKE_PACKAGE".tar.gz"
tar xf $CMAKE_PACKAGE.tar.gz
sudo mkdir /opt/cmake
sudo cp -r $CMAKE_PACKAGE/* /opt/cmake/
sudo ln -s /opt/cmake/bin/cmake /usr/bin/cmake*
cd -
