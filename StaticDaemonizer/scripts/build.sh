#!/bin/bash

# Variables
BUILD_TYPE=Release
PREFIX_PATH= #Your path to Qt

#Commands
mkdir $PWD/../build && cd $PWD/../build
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_PREFIX_PATH=$PREFIX_PATH
cmake --build . --target all
