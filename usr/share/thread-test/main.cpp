#include "time.h"
#include "threadable.h"
#include "physics.h"
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

        Time::USecond t3(1337);
        CHECK_EQUAL(1337, t3);

        Time::NSecond t4(31337);
        CHECK_EQUAL(31337, t4);

        Time::MSecond t5(313373);
        CHECK_EQUAL(313373, t5);
    }
    TEST(operations)
    {
        Time::Second t3 = 0;
        Time::Second t4 = t3 + 10;
        CHECK_EQUAL(10, t4);

        Time::Second t5 = t4 * 5;
        CHECK_EQUAL(50, t5);
    }
    TEST(conversions)
    {
        Time::Second s = 1;
        Time::USecond us (Time::toUSecond(s));
        CHECK_EQUAL(1000000, us);

        Time::MSecond ms (Time::toMSecond(s));
        CHECK_EQUAL(1000, ms);

        Time::NSecond ns (5 * 1e9);
        s = Time::toSecond(ns);
        CHECK_CLOSE(5, s, 5 * 0.00000001);
    }
    TEST(sleep1)
    {
        const Time::Second delay = 0.005;
        const float margin = 1+0.01;
        UNITTEST_TIME_CONSTRAINT((int)Time::toMSecond(delay*margin));
        Time::sleep(delay);
    }
    TEST(sleep2)
    {
        const Time::Second delay = 1;
        const float margin = 1+0.01;
        UNITTEST_TIME_CONSTRAINT((int)Time::toMSecond(delay*margin));
        Time::sleep(delay);
    }
    TEST(sleep3)
    {
        const Time::Second delay = 0.0005;
        const float margin = 1+0.01;
        UNITTEST_TIME_CONSTRAINT((int)Time::toMSecond(delay*margin));
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
SUITE(testThreadable)
{
    TEST(derivation)
    {
        shared_ptr<Physics> p (new Physics);
        CHECK(boost::dynamic_pointer_cast<Threadable>(p));
    }
    TEST(threading)
    {
    }
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
