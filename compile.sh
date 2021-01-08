#!/bin/bash

if [ -d "build" ]; then
    rm -rf "build"
fi
mkdir "build"
cd "build"

cmake -DCMAKE_BUILD_TYPE=Release ..
make -j16

cd ../tests
if ! ./test.sh; then
    exit $?
fi
cd ../build

sudo make install
