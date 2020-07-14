#!/bin/bash

if [ -d "build" ]; then
    rm -rf "build"
fi
mkdir "build"
cd "build"

cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
sudo make install

if [ -d ~/.ample ]; then
    rm -rf ~/.ample
fi
mkdir -p ~/.ample/libs

mv "AMPLE-Core/libCore.so" ~/.ample/libs/Core.so

cd ..
build/AMPLE-Runtime/AMPLE Examples/Hello\ World/Hello\ World.ample
