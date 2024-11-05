#!/bin/bash

clang -O0 main.c -o main \
    --target=arm-linux-gnueabihf \
    --sysroot=/usr/arm-linux-gnueabihf \
    --gcc-toolchain=/usr/arm-linux-gnueabihf \
    -Xclang -fdebug-pass-manager \
    -fsave-optimization-record \
    -Rpass=.* #-Rpass-missed=.* -Rpass-analysis=.*