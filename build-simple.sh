#!/bin/sh

[ -d bin ] || mkdir bin
c++ -O4 -o bin/countbits_test -lgtest -I src/countbits/include src/countbits/test/countbits_test.cc src/countbits/src/countbits.cc
