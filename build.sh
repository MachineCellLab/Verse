#!/bin/bash

CFLAGS=" -Iinc -Iother/linenoise "

#mkdir build

gcc $CFLAGS -c other/linenoise/linenoise.c

g++ $CFLAGS -c src/LineReader.cpp
g++ $CFLAGS -c src/Shell.cpp

# build test app
g++ $CFLAGS -o console-test *.o test/TestConsole.cpp


