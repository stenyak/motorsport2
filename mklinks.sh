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
mkcd usr
    mkcd include
        for i in ../share/*
        do
            if [ -d "$i"/include ]
            then
                if [ -h $(basename "$i") ]
                then
                    rm $(basename "$i")
                fi
                echo "Creating include link $i ..."
                ln -s "$i"/include $(basename "$i")
            fi
        done
    cd ..

    mkcd lib
        for i in ../share/*
        do
            if [ -d "$i"/lib ]
            then
                if [ -h $(basename "$i") ]
                then
                    rm $(basename "$i")
                fi
                echo "Creating lib link $i ..."
                ln -s "$i"/lib $(basename "$i")
            fi
        done
    cd ..

    mkcd bin
        for i in ../share/*
        do
            if [ -f $i/bin/$(basename $i) -o -f $i/bin/$(basename $i)D ]
            then
                echo "Creating bin link $i ..."
                if [ -f $(basename "$i") ]
                then
                    rm $(basename "$i")
                fi
                cp $cwd/run.sh ./$(basename $i)
            fi
        done
    cd ..
cd ..
