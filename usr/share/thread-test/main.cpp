#include "time.h"
using namespace motorsport;
#include <unittest++/UnitTest++.h>
#include <limits>
using namespace std;
#include <boost/shared_ptr.hpp>
using namespace boost;

SUITE(testTime)
{
    TEST(construction)
    {
        Time::Second t1(0);
        CHECK_EQUAL(0, t1);

        Time::Second t2 = 0;
        CHECK_EQUAL(0, t2);

        CHECK_EQUAL(t1, t2);
    }
    TEST(addition)
    {
        Time::Second t3 = 0;
        Time::Second t4 = t3 + 10;
        CHECK_EQUAL(10, t4);
    }
    TEST(sleep1)
    {
        const Time::Second delay = 0.000005;
        UNITTEST_TIME_CONSTRAINT(int(delay*1.01*1000.0));
        Time::sleep(delay);
    }
    TEST(sleep2)
    {
        const Time::Second delay = 1;
        UNITTEST_TIME_CONSTRAINT(int(delay*1.01*1000.0));
        Time::sleep(delay);
    }
    TEST(nowConstruction)
    {
        Time::Second t1 (Time::now());
        CHECK(t1 != 0);
        Time::Second t2 = Time::now();
        CHECK(t2 != 0);
    }
    TEST(nowCorrectness)
    {
        Time::Second delay = 0.5;
        Time::Second initial = Time::now();
        Time::sleep(delay);
        Time::Second final = Time::now();

        Time::Second expected = initial + delay;

        CHECK_CLOSE(expected, final, 0.01);
    }
    TEST(nowAccuracy)
    {
        CHECK(sizeof(Time::Second) > 8);
        CHECK((2038-1970)*365*24*60*60 < numeric_limits<Time::Second>::max());
    }
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
