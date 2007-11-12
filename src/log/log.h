#ifndef LOG_H_
#define LOG_H_

#include <string>
#define error(x, ...) log(Log::Error,__FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define warn(x, ...)  log(Log::Warn, __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define user(x, ...)  log(Log::User, __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define cont(x, ...)  log(Log::Cont, __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define dev(x, ...)   log(Log::Dev,  __FILE__,(int)(__LINE__),x,##__VA_ARGS__)
#define trace(x, ...) log(Log::Trace,__FILE__,(int)(__LINE__),x,##__VA_ARGS__)

namespace stk
{
class Log
{
  public:
    enum Level
    {
        Error = 0 // !< Can't continue, must be fixed
        ,Warn = 1 // !< Can continue, should be fixed
        ,User = 2 // !< Info for average joe
        ,Cont = 3 // !< Info for contents creators
        ,Dev = 4 // !< Debug info for code developers
        ,Trace = 5 // !< Verbose info for code developers
    };
    Log(std::string id);
    virtual ~Log();
    std::string log(Level level, std::string file, int line, std::string msg, ...);
  private:
    const std::string Log::getLevelString (Level level);
    std::string id;
};
}

#endif /*LOG_H_*/
