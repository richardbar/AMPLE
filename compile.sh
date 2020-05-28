#!/bin/bash
if [ -d "build/" ]; then
    rm -rf "build/"
fi

mkdir build
cd build/

cmake -DCMAKE_BUILD_TYPE=Release ../AMPLE-Core/
make
if [ -d "~/.ample" ]; then
    if [ -d "~./ample/libs" ]; then
        if [ -f "~/.ample/libs/Core.so" ]; then
            rm "~/.ample/libs/Core.so"
        fi
    fi
    rm -rf ~/.ample
fi
mkdir ~/.ample/libs && cp libCore.so ~/.ample/libs/Core.so

rm -rf *

cmake -DCMAKE_BUILD_TYPE=Release ../AMPLE-Runtime/
make

printf "\n"
./AMPLE ~/Projects/Program.ample
printf "\n"