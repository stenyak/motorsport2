import os
import sys
import re
from subprocess import Popen,PIPE

#first part of scons path
pwd = os.getenv("PWD")

#detect if current OS follows Filesystem Hierarchy Standard
fhs = pwd[:1] == "/"

#normalizing path only works with forward slashes,so we temporarily convert slashes on non-fhs systems
scons = pwd + "/" + os.path.dirname (sys.argv[0]) + "/deps/scons-local/scons.py"
if not fhs:
    scons = re.compile("\\\\").sub("/", scons)
scons = os.path.normpath(scons)
if not fhs:
    scons = re.compile("\/").sub("\\\\", scons)

#now that we got scons path, put the necessary parameters
cmd = "python \""+scons+"\" -Q"

if sys.argv[1] == "clean":
    cmd += " -c"
if sys.argv[1] == "all":
    cmd += ""

p = Popen(cmd, shell=True,stdout=PIPE,stderr=PIPE)
print (''.join(p.stdout.readlines() ))
print (''.join(p.stderr.readlines() ))

