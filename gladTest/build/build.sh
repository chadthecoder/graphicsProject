#! /usr/bin/bash

#delete build files except the one that executes stuff
find . ! -name 'build.sh' -name 'rebuild.sh' -type f -exec rm -f {} +

#build glm
cd ../include/glm
#rm -rf build
mkdir -p build
cd build
cmake ..
make
cd ../../../build

cmake ..
make
./OpenGLCube