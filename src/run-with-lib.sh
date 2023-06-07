#!/bin/bash

LD_LIBRARY_PATH=$(realpath "$0")
LD_LIBRARY_PATH=$(dirname $LD_LIBRARY_PATH)
export LD_LIBRARY_PATH

./wort

exec $SHELL
