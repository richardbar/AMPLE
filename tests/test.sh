#!/bin/bash

cd test1
../../build/bin/AMPLE-Assembler test.asm
../../build/bin/AMPLE-Runtime Out.ample -p > output.txt
if ! echo "c564c431d9fd38cc157642ed81f18559ec2172829fce2eb1da3c57fa7a644184 output.txt" | sha256sum --check --quiet; then
    echo "Error while trying to run test" >&2
    exit 1
fi
cd ..