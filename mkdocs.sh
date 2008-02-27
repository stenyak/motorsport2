#!/bin/bash
function mkcd {
    if [ ! -d $1 ]
    then
        echo "Creating $1 directory..."
        mkdir $1
    fi
    cd $1
}

cwd="`pwd`"
mkcd doc
    for i in ../usr/share/*
    do
        pushd .
        cd $i
            if [ -f Doxyfile ]
            then
                echo "Updating $i docs ..."
                doxygen
            fi
        popd
        if [ -d "$i"/doc/html ]
        then
            if [ -f $(basename "$i") ]
            then
                rm $(basename "$i")
            fi
            echo "Creating doc link $i ..."
            ln -s "$i"/doc/html $(basename "$i")
        fi
    done
cd ..
cd cwd
