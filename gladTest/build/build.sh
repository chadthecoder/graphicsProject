#! /usr/bin/bash

#delete build files except the one that executes stuff
find . ! -name 'build.sh' -type f -exec rm -f {} +

#build glm
cd ../include/glm
rm -rf build
mkdir build
cd build
cmake ..
make
cd ../../../build

cmake ..
make
./OpenGLCube