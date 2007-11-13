#ifndef MAIN_H_
#define MAIN_H_

/** \subsection Dependencies
 - Via web:
   - eclipse
     - doxygen plugin (web: http://download.gna.org/eclox/update)
     - cdt plugin (web)
     - cygwin
   - scons-local
   - testsoon
  - Via cygwin installer:
     - boost
     - g++
     - gdb
     - doxygen
*/

/** Motorsport entry point.
@param argc number of parameters. Currently 0..1
@param argv the parameter strings. E.g.: "help", "run", ... See source code for a complete list.
@returns 0 on success
@returns 1 if no option was provided
@returns 2 if help screen was triggered. */
int main(int argc, char*argv[]);

#endif /*MAIN_H_*/
