#/bin/bash

set -xe

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: $0 <version> <dir>"
    exit 1
fi
version=$1
outdir=$2
mkdir -p $outdir
curr_dir=$(pwd)
pushd $outdir
git init
git remote add origin https://github.com/python/cpython
git config --local gc.auto 0
git -c protocol.version=2 fetch --no-tags --prune --no-recurse-submodules --depth=1 origin +refs/heads/v$version*:refs/remotes/origin/v$version* +refs/tags/v$version*:refs/tags/v$version*
git checkout --progress --force refs/tags/v$version
git log -1 --format='%H'
git apply $curr_dir/add_decrypter.patch
popd
