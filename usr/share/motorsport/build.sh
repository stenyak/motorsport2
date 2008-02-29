#!/bin/sh
scons $* && LD_LIBRARY_PATH=. ./motorsport-testsD && gcov *.cpp && grep -H "####" *.cpp.gcov |sed "s/\.gcov:/:/g;s/[\ ]*#####:[\ ]*//g;s/$$/  \/\/warning: line not covered\./g"
