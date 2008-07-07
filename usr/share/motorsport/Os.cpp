
#include "Os.h"

namespace motorsport {

/** Locates the path to our application */
string Os::getSharePath()
{
  // Bouml preserved body begin 00020055
    #if MOTORSPORT_OS == MOTORSPORT_OS_APPLE
        char path[1024];
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        assert(mainBundle);
        CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
        assert(mainBundleURL);
        CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
        assert(cfStringRef);
        CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);
        CFRelease(mainBundleURL);
        CFRelease(cfStringRef);
        result = std::string(path) + "/Contents/Resources/";
    #else
        std::string result = "usr/share/motorsport-sim-tests/";
    #endif
    return result;
  // Bouml preserved body end 00020055
}
/** Returns the relative path to the data directory. */
string Os::getDataPath()
{
  // Bouml preserved body begin 0001F447
    return getSharePath() + "data/";
  // Bouml preserved body end 0001F447
}
/** Returns the relative path to the configuration directory. */
string Os::getCfgPath()
{
  // Bouml preserved body begin 0001F4C7
    return getSharePath() + "cfg/";
  // Bouml preserved body end 0001F4C7
}
/** Returns the relative path to the logs directory. */
string Os::getLogsPath()
{
  // Bouml preserved body begin 0001F547
    return getSharePath() + "logs/";
  // Bouml preserved body end 0001F547
}

} // namespace motorsport
