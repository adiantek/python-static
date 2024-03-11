#!/bin/bash

set -xe

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: $0 <version> <dir>"
    exit 1
fi
version=$1
dir=$2
cflags=""
ldflags="-pthread -lm -ldl -lutil"
if [ "$(uname)" == "Darwin" ]; then
    cflags+=" -mmacosx-version-min=11.0"
fi

gcc $cflags -c -o python3api.o python3api.c -I $dir/Include/ -I $dir/
cp $dir/libpython$version.a libpython3api.a
ar rcs libpython3api.a python3api.o

gcc $cflags -o python3api_test python3api_test.c libpython3api.a $ldflags
