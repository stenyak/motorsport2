#!/bin/bash
# resolve installation directory
cwd="`pwd`"
if [ -h "$0" ] ; then
    basename=`basename "$0"`
    script=`ls -l "$0" | sed "s/.*${basename} -> //g"`
    cd "`dirname "$0"`"
    cd "`dirname "$script"`"
else
    cd "`dirname "$0"`"
fi

binDir="`pwd`"
cd ..

# change back directory
cd "$cwd"


dirs="$binDir/../lib"
for i in $binDir/../lib/*
do
    dirs="$dirs:$i"
done

file=$binDir/../share/$(basename $0)/bin

if   [ -f $file/$(basename $0) ]
then
    file=$file/$(basename $0)
elif [ -f $file/$(basename $0)D ]
then
    file=$file/$(basename $0)D
else
    echo "Error, executable file not found :-("
fi

LD_LIBRARY_PATH="$dirs" $file
