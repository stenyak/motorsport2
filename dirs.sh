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
binPath=`basename "$0"`".bin"
instDir="`pwd`"

# change back directory
cd "$cwd"

echo cwd=$cwd
echo binDir=$binDir
echo binPath=$binPath
echo shareDir=$instDir

