How to develop Motorsport Project under GNU/Linux
=================================================

First, you need to install certain libs using your distros package manager.
 - boost-1.35 (thread, shared_ptr, bind, date_time)
 - unittest++ (*)

* Note:  If your distro (such as Gentoo) doesn't provide unittest++, we
provide a way to install it for usage in Motorsport development. This script
depends on subversion, so install it before running.
$ ./grabDeps.sh


Development flow:
 - For changing anything different than method bodies, use BoUML and its C++
 code generator. The BoUML project is located at uml/motorsport.
 - For method bodies, edit usr/share/*/*.cpp files with your usual editor.
 - Once the projects are built, you can use run.sh in order to execute them.

Building all projects at once:
$ scons

Building all projects at once, and testing/debugging once of them:
$ build*.sh

Cleaning up all files:
$ ./clean.sh
