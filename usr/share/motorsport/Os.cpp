
#include "Os.h"

namespace motorsport {

/** Provides a nice cross platform solution for locating the data files. On windows files are searched for in the current working directory, on OS X however you must provide the full path, the helper function getSharePath does this for us. */
string Os::getResourcePath()
{
  // Bouml preserved body begin 000200D5
    std::string result = ".";
    #if MOTORSPORT_OS == MOTORSPORT_OS_APPLE
        result = getSharePath() + "Contents/Resources";
    #else
        result = getSharePath();
    #endif
    return result + "/";
  // Bouml preserved body end 000200D5
}
/** Locates the path to our application */
string Os::getSharePath()
{
  // Bouml preserved body begin 00020055
    std::string result = "usr/share/motorsport-sim-tests";
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
        result = std::string(path);
    #endif
    return result + "/";
  // Bouml preserved body end 00020055
}

} // namespace motorsport
