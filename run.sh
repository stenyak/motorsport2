#!/bin/bash
if [ "$*" == "" ]
then
    echo "Please specify a binary name from these:"
    echo -n "   "
    ls usr/bin
else
    for i in $*
    do
        bin=usr/bin/$i
        echo Running $bin...
        LD_LIBRARY_PATH="usr/lib:usr/lib/motorsport:usr/lib/motorsport-sim" $bin
        #gcov usr/share/*/*.cpp |grep -e "File\ '[^\/].*" -A 1
        gcov usr/share/*/*.cpp
        #grep -H "####" usr/share/$i/*.cpp.gcov |sed "s/\.gcov:/:/g;s/[\ ]*#####:[\ ]*//g;s/$$/  \/\/warning: line not covered\./g"
        echo ""
    done
fi
