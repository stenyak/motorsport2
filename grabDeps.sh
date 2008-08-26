#!/bin/bash

cpus=$(cat /proc/cpuinfo  |grep processor |wc -l)

function mkcd
{
    if [ ! -d $1 ]
    then
        echo "Creating $1 directory..."
        mkdir -p $1
    fi
    cd $1
}

function unittest
{
    mkcd deps
        echo "==== Installing UnitTest++ ===="
        echo " - Grabbing from svn..."
        svn co https://unittest-cpp.svn.sourceforge.net/svnroot/unittest-cpp unittest-cpp
        echo " - Building..."
        cd unittest-cpp/UnitTest++
            make -j $cpus
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
}

function scons
{
    mkcd deps
        echo "==== Installing SCons ===="
        echo " - Grabbing from svn..."
        svn checkout http://scons.tigris.org/svn/scons/trunk scons --username guest --password ""
        echo " - Building..."
        cd scons
            export SCONS_LIB_DIR=`pwd`/src/engine
            python src/script/scons.py build/scons
            echo " - Copying files..."
            cd build/scons
                python setup.py install --prefix=../../../../usr
            cd ../..
        cd ..
        echo "==== SCons installed ===="
    cd ..
}

function freeimage
{
    mkcd deps
        echo "==== Installing FreeImage ===="
        echo " - Grabbing from cvs..."
        echo "Press enter to continue (empty password)."
    cvs -d:pserver:anonymous@freeimage.cvs.sourceforge.net:/cvsroot/freeimage login
    cvs -z3 -d:pserver:anonymous@freeimage.cvs.sourceforge.net:/cvsroot/freeimage co -P FreeImage
        echo " - Building..."
        cd Freeimage
            # specify custom prefix by hand:
            t=$(tempfile)
            cat Makefile.gnu |sed "s/\/usr/\/\.\.\/\.\.\/usr/g;s/-.\ root//g" > $t; cp $t Makefile.gnu
            rm $t
            make -j $cpus
            echo " - Copying files..."
            make install
        cd ..
        echo "==== FreeImage installed ===="
    cd ..
}

function ogre
{
    mkcd deps
        echo "==== Installing Ogre ===="
        echo " - Grabbing from svn..."
        svn co https://svn.ogre3d.org/svnroot/ogre/trunk ogre
        echo " - Building..."
        cd ogre
            ./bootstrap
            ./configure --prefix=$PWD/../../usr
            make -j $cpus
            echo " - Copying files..."
            make install
        cd ..
        echo "==== Ogre installed ===="
    cd ..
}

function ogrecollada
{
    mkcd deps
        echo "==== Installing OgreCollada ===="
        echo " - Grabbing from svn..."
        svn co https://ogrecollada.svn.sourceforge.net/svnroot/ogrecollada/trunk ogrecollada
        echo " - Building..."
        cd ogrecollada
            cd premake
                PKG_CONFIG_PATH="$PWD/../../../usr/lib/pkgconfig" premake --verbose --target gnu
                PKG_CONFIG_PATH="$PWD/../../../usr/lib/pkgconfig" make -j $cpus
            cd ..
            echo " - Copying files..."
            cp bin/release/lib* ../../usr/lib
            cp OgreCollada/OgreCollada/include/*.h ../../usr/include
        cd ..
        echo "==== OgreCollada installed ===="
    cd ..
}

function boost
{
    mkcd deps
        echo "==== Installing Boost ===="
        echo " - Grabbing from svn..."
        svn co http://svn.boost.org/svn/boost/trunk boost-trunk -r 46712 #v1.35
        echo " - Building..."
        cd boost-trunk
            ./configure --prefix=$PWD/../../usr
            make -j $cpus
            echo " - Copying files..."
            make install
        cd ..
        echo "==== Boost installed ===="
    cd ..
}

function bullet
{
    mkcd deps
        echo "==== Installing Bullet ===="
        echo " - Grabbing from svn..."
        svn checkout http://bullet.googlecode.com/svn/trunk bullet
        echo " - Building..."
        cd bullet
            ./configure --prefix=$PWD/../../usr
            make -j $cpus
            echo " - Copying files..."
            jam install
        cd ..
        echo "==== Bullet installed ===="
    cd ..
}

params="unittest scons freeimage ogre ogrecollada boost bullet"

if [ "$*" != "" ]; then
    params="$*"
fi

for i in $params
do
    case "$i" in
        "unittest") unittest;;
        "scons") scons;;
        "freeimage") freeimage;;
        "ogre") ogre;;
        "ogrecollada") ogrecollada;;
        "boost") boost;;
        "bullet") bullet;;
        *) ;;
    esac
done
