#!/bin/sh
pushd .
cd ../../..
./mklinks.sh
popd
scons $* && LD_LIBRARY_PATH="../../lib/motorsport:." ./motorsport-tests && echo "--------------------" && gcov *.cpp |grep -e "File\ '[^\/].*" -A 1 && echo "--------------------" && grep -H "####" *.cpp.gcov |sed "s/\.gcov:/:/g;s/[\ ]*#####:[\ ]*//g;s/$$/  \/\/warning: line not covered\./g"
