#!/bin/bash

DIR=/usr/include/Daemonizer

sudo make uninstall

if [ -d $DIR ]
then
    sudo rm -rf $DIR
    echo "rm -rf $DIR"
else
    echo "$DIR doesn't exist!"
fi

sudo make distclean
rm -f uninstall
