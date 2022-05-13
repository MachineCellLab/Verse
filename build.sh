#!/bin/bash

CFLAGS += "-Iinc"

gcc $CFLAGS -c other/linenoise/linenoise.c

g++ $CFLAGS -c src/LineReader.cpp
g++ $CFLAGS -c src/Shell.cpp

# main test driver
g++ $CFLAGS -c TestConsole.cpp

#g++ $CFLAGS -o testConsole *.o TestConsole.cpp


