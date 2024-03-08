#/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <outdir>"
    exit 1
fi
outdir=$1
version="3.12.2"
mkdir -p $outdir
pushd $outdir
git init
git remote add origin https://github.com/python/cpython
git config --local gc.auto 0
git -c protocol.version=2 fetch --no-tags --prune --no-recurse-submodules --depth=1 origin +refs/heads/v$version*:refs/remotes/origin/v$version* +refs/tags/v$version*:refs/tags/v$version*
git checkout --progress --force refs/tags/v$version
git log -1 --format='%H'
popd
