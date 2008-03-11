How to develop Motorsport Project under GNU/Linux
=================================================

First, you need to install certain libs using your distros package manager.
 - boost
 - unittest++ (*)

* Note:  If your distro (such as Gentoo) doesn't provide unittest++, we
provide a way to install it for usage in Motorsport development. This script
depends on subversion, so install it before running.
$ ./grabDeps.sh


Development flow:
 - For changing anything different than method bodies, use BoUML and its C++
 code generator. The BoUML project is located at uml/motorsport.
 - For method bodies, edit usr/share/*/*.cpp files with your usual editor.
 - Motorsport Simulator depends on Motorsport (core).
 - Once the projects are built, you can run usr/bin/* in order to execute
   them. They use an ugly hack in order to be usable without installing to
   /usr or /usr/local.

Building Motorsport:
$ pushd .
$ cd usr/share/motorsport
$ scons
$ popd
$ ./mklinks.sh

Building Motorsport Simulator:
$ pushd .
$ cd usr/share/motorsport-sim
$ scons
$ popd
$ ./mklinks.sh
