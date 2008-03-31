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
    result += (Second)(ts.tv_sec);
    result += toSecond((NSecond)(ts.tv_nsec));
    return result;
}
void Time::sleep(Second seconds)
{
    usleep((int)toUSecond(seconds));
}
Time::USecond Time::toUSecond(Second seconds)
{
    return seconds * 1e6;
}
Time::Second Time::toSecond(NSecond nseconds)
{
    return nseconds * 1e-9;
}
timespec Time::getTime()
{
    timespec result;
    if (0 != clock_gettime(CLOCK_REALTIME, &result))
        throw "Couldn't get system time";
    return result;
}

