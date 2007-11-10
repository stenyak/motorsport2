#!/bin/bash
incPaths="-I../deps/log/include -I/usr/include/boost-1_33_1"
libPaths="-L../deps/log/lib"
libs="-lboost_program_options-gcc-mt -llog"
flags="-Wall -Wextra -pedantic"
sources="*.cpp"
object="motorsport.exe"
g++ $sources -o $object $flags $incPaths $libPaths $libs   
