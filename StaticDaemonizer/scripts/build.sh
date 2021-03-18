#!/bin/bash

# Variables
BUILD_DIR=$PWD/../build

#Commands
if [[ -d $BUILD_DIR ]]
then
  rm -rf $BUILD_DIR
fi

mkdir $PWD/../build && cd $PWD/../build
cmake ..
make
