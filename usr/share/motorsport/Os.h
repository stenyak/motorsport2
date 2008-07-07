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

/** Handles all OS specific issues. Also, it guesses the current operating system, and defines MOTORSPORT_OS_PLATFORM accordingly. */
class Os {
  private:
    /** Locates the path to our application */
    static string getSharePath();

  public:
    /** Returns the relative path to the data directory. */
    static string getDataPath();
    /** Returns the relative path to the configuration directory. */
    static string getCfgPath();
    /** Returns the relative path to the logs directory. */
    static string getLogsPath();
};

} // namespace motorsport
#endif
