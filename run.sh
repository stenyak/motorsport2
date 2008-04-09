#!/bin/bash
if [ "$1" == "" ]
then
    echo "Please specify a binary name from these:"
    echo -n "   "
    ls usr/bin
else
    LD_LIBRARY_PATH="usr/lib:usr/lib/motorsport:usr/lib/motorsport-sim" usr/bin/$1
fi
