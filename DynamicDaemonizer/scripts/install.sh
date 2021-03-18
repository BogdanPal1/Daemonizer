#!/bin/bash

# Installing library
if [[ -d $PWD/../build ]]
then
    cd $PWD/../build
    make install
else
    echo "You must to build library first."
    echo "Please run build.sh"
fi
