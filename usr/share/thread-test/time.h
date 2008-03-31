#include <time.h>
#include <unistd.h>
namespace motorsport
{
class Time
{
    public:
        typedef long double Second;
        static Second now();
        static void sleep(Second seconds);
    private:
        static timespec getTime();
};
}

