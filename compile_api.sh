#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <dir>"
    exit 1
fi

dir=$1

gcc -c -o python3api.o python3api.c -I $1/Include/ -I $1/
cp $1/libpython3.12.a libpython3api.a
ar rcs libpython3api.a python3api.o
gcc -o python3api -DPYTHON3API_TEST python3api.c -I $1/Include/ -I $1/ -lm
