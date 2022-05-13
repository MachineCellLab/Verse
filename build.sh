#!/bin/bash

gcc -c linenoise/linenoise.c
g++ -c LineReader.cpp
g++ -c Shell.cpp
g++ -o testConsole *.o TestConsole.cpp
