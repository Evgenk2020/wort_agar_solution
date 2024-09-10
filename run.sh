#!/bin/bash

./build/app/bin/wort -h
echo "------------------------------"
./build/app/bin/wort -df 22 4.5 450

exec $SHELL
