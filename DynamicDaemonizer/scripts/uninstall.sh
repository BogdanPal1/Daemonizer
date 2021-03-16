#!/bin/bash

DIR=/usr/include/Daemonizer

make uninstall

if [ -d $DIR ]
then
    rm -rf $DIR
    echo "rm -rf $DIR"
else
    echo "$DIR doesn't exist!"
fi

make distclean
rm -f uninstall
