#!/bin/bash

LIB_PATH=/usr/local/lib/Daemonizer
INCLUDE_PATH=/usr/local/include/Daemonizer

if [[ -d $LIB_PATH && -d $INCLUDE_PATH ]]
then
    sudo rm -rf $LIB_PATH
    echo "rm -rf $LIB_PATH"
    sudo rm -rf $INCLUDE_PATH
    echo "rm -rf $INCLUDE_PATH"
else
    echo "$LIB_PATH doesn't exist!"
    echo "$INCLUDE_PATH doesn't exist!"
fi

