/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_OS_H
#define MOTORSPORT_OS_H
#define MOTORSPORT_OS_WIN32 1
#define MOTORSPORT_OS_LINUX 2
#define MOTORSPORT_OS_APPLE 3

#if defined( __WIN32__ ) || defined( _WIN32 )
    #define MOTORSPORT_OS MOTORSPORT_OS_WIN32
#elif defined( __APPLE_CC__)
    #define MOTORSPORT_OS MOTORSPORT_OS_APPLE
#else
    #define MOTORSPORT_OS MOTORSPORT_OS_LINUX
#endif

#if MOTORSPORT_OS == MOTORSPORT_OS_APPLE
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include <string>
using namespace std;
#include <boost/filesystem/operations.hpp>

namespace motorsport { class Exception; } 

namespace motorsport {

/** Handles all OS specific issues. Also, it guesses the current operating system, and defines MOTORSPORT_OS_PLATFORM accordingly. */
class Os {
  private:
    /** Locates the path to our application resources directory (share in unix systems). */
    static string getSharePath(const string & filepath);

  public:
    /** Returns the relative path to the specified data file. The file must exist. */
    static string getDataPath(const string & filepath);
    /** Returns the relative path to the specified configuration file. The file must exist. */
    static string getCfgPath(const string & filepath);
    /** Returns the relative path to the specified log filename. The file must exist.*/
    static string getLogsPath(const string & filepath);
    /** Checks if the file is readable.
    \param filepath the path and name, either absolute or relative, of the file that is to be checked for readability.
    \returns true if file can be read.
    \returns false if file can not be read. */
    static bool isFileReadable(const string & filepath);
};

} // namespace motorsport
#endif
