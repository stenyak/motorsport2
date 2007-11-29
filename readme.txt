General Developer instructions:
-------------------------------
-Install cygwin, its usual tools (sed, grep, ...), and boost libraries.

-Download scons-local-0.97 and place it in ./deps/scons-local:
stenyak@1ksurvivor~/home/dev/motorsport$ ls deps/scons-local/
scons-LICENSE  scons-README  scons-local-0.97  scons-time.py  scons.py  sconsign.py

-Download test soon and place it in ./deps/testsoon:
stenyak@1ksurvivor~/home/dev/motorsport$ ls deps/testsoon/
Doxyfile  SConstruct  help  include  src

-You can access the online documentation at http://motorsport.stenyak.com/trunk/doc/ It may not be very up to date though. You can also generate the documentation by yourself if you chdir into the project dirs and then run "doxygen".
stenyak@1ksurvivor~/home/dev/motorsport$ cd src/log/
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ doxygen
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ cd ../motorsport
stenyak@1ksurvivor~/home/dev/motorsport/src/motorsport$ doxygen
stenyak@1ksurvivor~/home/dev/motorsport/src/motorsport$ ls ../../doc/
dirs.txt  log  motorsport

Eclipse Developer Instructions:
-------------------------------
Open Eclipse.
Switch to the workspace in ./
If it doesn't work, import each directory in ./src/* as a project.
You should be able to build, debug, and everything now.

Vim/Other Developer Instructions:
---------------------------------
There's 2 ways, they do the same thing. One uses a wrapper designed for eclipse, the other doesn't. Use any of them. Replace "log" with whatever project at ./src/* you want to develop.
-Eclipse way:
stenyak@1ksurvivor~/home/dev/motorsport$ cd src/log/
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ python ../../scons.py clean
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ python ../../scons.py all
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ gdb dtests.exe

-Regular way:
stenyak@1ksurvivor~/home/dev/motorsport$ cd src/log/
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ python ../../deps/scons-local/scons.py -Q -c
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ python ../../deps/scons-local/scons.py -Q
stenyak@1ksurvivor~/home/dev/motorsport/src/log$ gdb dtests.exe

General Developer instructions:
-------------------------------
Once compiled, the generated files will have been *copied* to ./usr/{bin,lib,share,...}, where different ./src/* projects can find and use them (as if they were installed to /usr).
