#!/bin/bash
mkdir include
mkdir lib
mkdir bin

cd include
    for i in ../share/*
    do
        echo "Creating include links! $i"
        ln -s "$i"/include $(basename "$i")
    done
cd ..

cd lib
    for i in ../share/*
    do
        echo "Creating lib links! $i"
        ln -s "$i"/lib $(basename "$i")
    done
cd ..

cd bin
    for i in ../share/*
    do
        echo "Creating bin links! $i"
        if [ -f $i/$(basename $i) -o -f $i/$(basename $i)D ]
        then
            cp ../run.sh ./$(basename $i)
        fi
    done
cd ..
