#!/bin/bash
if [ "$*" == "" ]
then
    echo "Please specify a binary name from these:"
    echo -n "   "
    ls usr/bin
else
    for i in $*
    do
        if [ ! -f "usr/bin/$i" ]; then exit; fi
        echo ">>> Running $bin..."
        for j in *.gc*; do rm "$j" 2>/dev/null; done
        LD_LIBRARY_PATH="usr/lib:usr/lib/motorsport:usr/lib/motorsport-sim" usr/bin/$i
        for k in usr/share/*/*.gcda
        do
            cp -f $(dirname "$k")/*.gc* . 2>/dev/null
        done

        echo ">>> Checking coverage..."
        for l in usr/share/*/*.gcda
        do
            gcov -p $(dirname "$l")/*.cpp |grep -e "File\ '[^\/].*" -A 1 2>/dev/null 1>/dev/null
        done

        grep -H "####" *.gcov  2>/dev/null|grep "^usr#share"  2>/dev/null|sed "s/\.gcov:/:/g;s/\([0-9]\):/\1: warning: line not covered\./;s/[\ ]*#####:[\ ]*//g;s/#/\//g;s/\^/\.\./g"
        rm *.gc* 2>/dev/null
        echo ""
    done
fi
