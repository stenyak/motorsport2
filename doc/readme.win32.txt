How to develop Motorsport Project under WindowsXP
=================================================

In order to download Motorsport, you can use Tortoise HG:
 - http://www.selenic.com/mercurial/wiki/index.cgi/TortoiseHg 
Or also the one provided by cygwin.

First, you need to install certain libs using CygWin:
 - boost-devel
 - gcc/g++
 - make
 - subversion
There are some more libs that have to be manually installed:
 - unittest++ (1)
 - scons (1,2)

(1) Run the following command at the Motorsport directory:
$ ./grabDeps.sh
(2) You may want to put SCons in your path; otherwise you'll later have to run
it specifying its install dir, which is usr/bin/scons

Development flow:
 - For changing anything different than method bodies, use BoUML and its C++
 code generator. The BoUML project is located at uml/motorsport.
 - For method bodies, edit usr/share/*/*.cpp files with your usual editor.
 - Once the projects are built, you can run ##TODO## in order to execute them.

Building all projects at once:
$ scons
