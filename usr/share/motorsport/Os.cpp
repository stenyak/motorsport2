
#include "Os.h"
#include "Exception.h"

namespace motorsport {

/** Locates the path to our application resources directory (share in unix systems). */
string Os::getSharePath(const string & filepath)
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
    result += filepath;
    if (!isFileReadable(result))
        throw motorsport::Exception ("Cannot access the specified file \""+result+"\"");
    return result;
  // Bouml preserved body end 00020055
}
/** Returns the relative path to the specified data file. The file must exist. */
string Os::getDataPath(const string & filepath)
{
  // Bouml preserved body begin 0001F447
    if (filepath == "")
        throw motorsport::Exception ("File path not especfied.");
    return getSharePath("data/" + filepath);
  // Bouml preserved body end 0001F447
}
/** Returns the relative path to the specified configuration file. The file must exist. */
string Os::getCfgPath(const string & filepath)
{
  // Bouml preserved body begin 0001F4C7
    if (filepath == "")
        throw motorsport::Exception ("File path not especfied.");
    return getSharePath("cfg/" + filepath);
  // Bouml preserved body end 0001F4C7
}
/** Returns the relative path to the specified log filename. The file must exist.*/
string Os::getLogsPath(const string & filepath)
{
  // Bouml preserved body begin 0001F547
    if (filepath == "")
        throw motorsport::Exception ("File path not especfied.");
    return getSharePath("logs/" + filepath);
  // Bouml preserved body end 0001F547
}
/** Checks if the file is readable.
\param filepath the path and name, either absolute or relative, of the file that is to be checked for readability.
\returns true if file can be read.
\returns false if file can not be read. */
bool Os::isFileReadable(const string & filepath)
{
  // Bouml preserved body begin 0001F5C7
    bool result = false;
    using namespace boost::filesystem;
    path fsfilepath = system_complete(path(filepath,native));
    if ( exists(fsfilepath) )
        result = true;
    return result;
  // Bouml preserved body end 0001F5C7
}

} // namespace motorsport
