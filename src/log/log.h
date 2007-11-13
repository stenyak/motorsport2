#ifndef LOG_H_
#define LOG_H_

#include <string>

/** Macros that call the appropriate log methods. */
#define error(x, ...) log(Log::Error,__FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define warn(x, ...)  log(Log::Warn, __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define user(x, ...)  log(Log::User, __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define cont(x, ...)  log(Log::Cont, __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define dev(x, ...)   log(Log::Dev,  __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define trace(x, ...) log(Log::Trace,__FILE__,(int)(__LINE__),x,##__VA_ARGS__)

/** Namespace for libraries that could be made independent from Motorsport. */
namespace stk
{
/** Logging class. It currently only outputs to std::cout. It has several \ref level "levels" of priority, and allows to identify each log instance with an \ref id. */
class Log
{
  public:
    /** Level of priority of the messages. */
    enum Level
    {
        Error = 0 // !< Can't continue, must be fixed
        ,Warn = 1 // !< Can continue, should be fixed
        ,User = 2 // !< Info for average joe
        ,Cont = 3 // !< Info for contents creators
        ,Dev = 4 // !< Debug info for code developers
        ,Trace = 5 // !< Verbose info for code developers
    };
    /** Creates a log instance.
    @param id any string that helps identify this particular log instance. */
    Log(std::string id);
    /** Destructor */
    virtual ~Log();
    /** Logs the desired message.
    @param level the level of priority of the message
    @param file the source code filename, from which the log was invoked.
    @param line the line of code where the call to the log was done.
    @param msg the log message, in printf format.
    @param ... the varargs, used in conjunction with msg.
    @returns the string that gets logged, once formatting has taken place. */
    std::string log(Level level, std::string file, int line, std::string msg, ...);
  private:
    /** Converts a priority \ref level into an string.
    @param level the desired priority \ref level to be converted.
    @returns an string that is later usually used in the output log string. */
    const std::string getLevelString (Level level);
    /** A string that helps identify the currnet log instance. */
    std::string id;
};
}

#endif /*LOG_H_*/
