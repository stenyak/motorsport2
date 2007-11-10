#!/bin/bash
incPaths="-I/usr/include/boost-1_33_1"
libPaths=""
libs=""
flags="-c -Wall -Wextra -pedantic"
sources="*.cpp"
object="log.o"
g++ $sources -o $object $flags $incPaths $libPaths $libs   

incPaths=""
libPaths=""
libs=""
flags="-shared"
sources="log.o"
object="libLog.so"
g++ $sources -o $object $flags $incPaths $libPaths $libs

libPath="../deps/log"
headers="*.h"
cp $object $libPath/lib
cp $headers $libPath/include