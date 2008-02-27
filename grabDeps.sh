#!/bin/bash
function mkcd {
    if [ ! -d $1 ]
    then
        echo "Creating $1 directory..."
        mkdir -p $1
    fi
    cd $1
}

mkcd deps
    echo "==== Installing UnitTest++ ===="
    echo " - Grabbing from svn..."
    svn co https://unittest-cpp.svn.sourceforge.net/svnroot/unittest-cpp unittest-cpp
    echo " - Building..."
    cd unittest-cpp/UnitTest++
        make
    cd ../..
    echo " - Copying libraries..."
    mkdir -p ../usr/lib
    cp unittest-cpp/UnitTest++/libUnitTest++.a ../usr/lib
    echo " - Copying headers..."
    mkdir -p ../usr/include/unittest++
    cp -r unittest-cpp/UnitTest++/src/* ../usr/include/unittest++/
    find ../usr/include/unittest++/ -name '*.[do]' -exec rm {} \;
    find ../usr/include/unittest++/ -name '*.cpp' -exec rm {} \;
    find ../usr/include/unittest++/ -type d -name '.svn' -exec rm -rf {} \;
    echo "==== UnitTest++ installed ===="

cd ..
