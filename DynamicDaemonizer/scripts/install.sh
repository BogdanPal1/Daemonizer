#!/bin/bash

# Variable that holds path to directory for header file
DIR=/usr/include/Daemonizer

# Installing library
make install
mkdir $DIR
cp daemonizer.h $DIR
cp daemonizer_global.h $DIR

# Cleaning our room
make clean
rm -f install
