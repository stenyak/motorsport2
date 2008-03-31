#include <exception>
using namespace std;
#include "time.h"
using namespace motorsport;
Time::Second Time::now()
{
    Time::Second result = 0;

    time_t rawtime;
    ::time(&rawtime);

    tm rawtime2;
    localtime_r(&rawtime, &rawtime2);

    timespec ts = getTime();
    result += (long double)(ts.tv_sec);
    result += (long double)(ts.tv_nsec) / (long double)(1000000000);
    return result;
}
void Time::sleep(Second seconds)
{
    usleep((int)(seconds*1000000.0));
}
timespec Time::getTime()
{
    timespec result;
    if (0 != clock_gettime(CLOCK_REALTIME, &result))
        throw "Couldn't get system time";
    return result;
}

