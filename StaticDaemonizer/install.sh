#!/bin/bash

# Variable that holds path to directory for header file
DIR=/usr/include/Daemonizer

# Installing library
sudo make install
sudo mkdir $DIR && sudo cp daemonizer.h $DIR

# Cleaning our room
make clean
rm -f install
