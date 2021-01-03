#!/bin/bash

if [ -d "build" ]; then
    rm -rf "build"
fi
mkdir "build"
cd "build"

cmake -DCMAKE_BUILD_TYPE=Release ..
make -j16
sudo make install
