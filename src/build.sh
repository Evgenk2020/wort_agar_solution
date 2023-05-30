#!/bin/bash

CURR_DIR=$(dirname $(realpath "$0"))
BUILD_TARGET=$CURR_DIR/build

#rm -rd $BUILD_TARGET

if [ -d $BUILD_TARGET ]
then
    cd $BUILD_TARGET
else
    mkdir $BUILD_TARGET
    cd $BUILD_TARGET
fi

cmake -B $BUILD_TARGET -S $CURR_DIR
cmake --build .

exec $SHELL