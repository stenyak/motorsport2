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

namespace motorsport {


class Os {
  public:
    /** Provides a nice cross platform solution for locating the data files. On windows files are searched for in the current working directory, on OS X however you must provide the full path, the helper function getSharePath does this for us. */
    static string getResourcePath();
    /** Locates the path to our application */
    static string getSharePath();
};

} // namespace motorsport
#endif
