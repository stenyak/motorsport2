#!/bin/bash
if [ "$*" == "" ]
then
    echo "Please specify a binary name from these:"
    echo -n "   "
    ls usr/bin
else
    for i in $*
    do
        echo ">>> Running $bin..."
        LD_LIBRARY_PATH="usr/lib:usr/lib/motorsport:usr/lib/motorsport-sim" usr/bin/$i
        for j in *.gc*; do rm "$j"; done
        for j in usr/share/*/*.gcda
        do
            cp -f $(dirname "$j")/*.gc* .
        done

        echo ">>> Checking coverage..."
        for j in usr/share/*/*.gcda
        do
            gcov -p $(dirname "$j")/*.cpp |grep -e "File\ '[^\/].*" -A 1 2>/dev/null 1>/dev/null
        done

        echo ">>> Showing lines..."
        grep -H "####" *.gcov |grep "^usr#share" |sed "s/\.gcov:/:/g;s/\([0-9]\):/\1: warning: line not covered\./;s/[\ ]*#####:[\ ]*//g;s/#/\//g;s/\^/\.\./g"
        rm *.gc*
        echo ""
    done
fi
