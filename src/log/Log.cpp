#include "Log.h"
#include <iostream.h>
#include <sstream>
#include <cstdarg>
using namespace std;
/*
 void _init()
 {
 printf("Inside _init()\n"); 
 } 
 void _fini()
 {
 printf("Inside _fini()\n"); 
 }
 */
namespace stk
{
Log::Log(std::string id)
{
    this->id = id;
}
Log::~Log()
{
}
std::string Log::log(Level level, std::string file, int line, std::string msg, ...)
{
    stringstream result;

    char buffer[2048];
    va_list arglist;
    va_start (arglist, msg);
    vsnprintf(buffer, sizeof (buffer), msg.c_str(), arglist);
    va_end (arglist);

    result<< getLevelString(level)<< ": "<< file<< "("<< this->id<< "):"<< line<< ": "<< buffer;
    cout<< result.str()<< endl;
    return result.str();
}
const std::string Log::getLevelString (Level level)
{
    string result;
    switch (level)
    {
        case Error:result = "EE"; break;
        case Warn: result = "WW"; break;
        case User: result = "II"; break;
        case Cont: result = "CC"; break;
        case Dev:  result = "d "; break;
        case Trace:result = "t "; break;
        default:   result = "  "; break;
    }
    return result;
}
}
