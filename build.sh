#!/bin/sh
mkdir bin
cd bin
cmake -DBUILD_TESTS=ON ..
make
cd tests
ctest -VV
