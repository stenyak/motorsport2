#include <time.h>
#include <unistd.h>
namespace motorsport
{
class Time
{
    public:
        typedef long double Second;
        typedef long double USecond;
        typedef long double NSecond;
        static Second now();
        static void sleep(Second seconds);
        static USecond toUSecond(Second seconds);
        static Second toSecond(NSecond nseconds);
    private:
        static timespec getTime();
};
}

