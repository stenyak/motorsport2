#ifndef MOTORSPORT_H_
#define MOTORSPORT_H_

/** \subsection Dependencies
 - Web:
   - eclipse
     - doxygen plugin (web: http://download.gna.org/eclox/update)
     - cdt plugin (web)
     - cygwin
   - scons
  - Cygwin:
     - boost
     - g++
     - gdb
     - cppunit
     - doxygen
     
*/

int main(int argc, char*argv[]);

class Motorsport
{
  public:
	Motorsport();
	int main(int argc, char*argv[]);
	virtual ~Motorsport();
};

#endif /*MOTORSPORT_H_*/
