#/bin/bash

set -xe

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
git -c protocol.version=2 fetch --no-tags --prune --no-recurse-submodules --depth=1 origin +refs/heads/v3.12.2*:refs/remotes/origin/v3.12.2* +refs/tags/v3.12.2*:refs/tags/v3.12.2*
git checkout --progress --force refs/tags/v3.12.2
git log -1 --format='%H'
popd
