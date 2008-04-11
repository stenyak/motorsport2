#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
#include <boost/thread/thread.hpp>
using namespace boost;

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
    TEST(operations)
    {
        using namespace boost::gregorian;

        //set initial date
        ptime t1(date(2002,2,10), time_duration(1,2,0));

        //set initial date + 10 seconds
        ptime t2(date(2002,2,10), time_duration(1,2,10));
        //add 10 seconds to initial date
        time_duration td1(0,0,10);
        ptime t3(t1+td1);

        //check both are the same
        CHECK_EQUAL(t2, t3);


        //multiplay offset by 5 (50seconds)
        ptime t4(t1+td1*5);
        ptime t5(date(2002,2,10), time_duration(1,2,50));
        CHECK_EQUAL(t4, t5);
    }
    TEST(conversions)
    {
        //unit of comparison: 1 second
        time_duration td(0,0,1);

        time_duration td1 = seconds(1);
        CHECK_EQUAL(td, td1);

        time_duration td2 = milliseconds(1000);
        CHECK_EQUAL(td, td2);

        time_duration td3 = microseconds(1000000);
        CHECK_EQUAL(td, td3);

    }
    TEST(sleep1)
    {
        boost::thread make_thread();
        int ms = 50;
        float margin = 1.02;
        time_duration td = milliseconds(ms);
        UNITTEST_TIME_CONSTRAINT(ms*margin);
        boost::this_thread::sleep(td);
    }
    TEST(sleep2)
    {
        boost::thread make_thread();
        int ms = 500;
        float margin = 1.01;
        time_duration td = milliseconds(ms);
        UNITTEST_TIME_CONSTRAINT(ms*margin);
        boost::this_thread::sleep(td);
    }
    TEST(nowCorrectness)
    {
        boost::thread make_thread();
        int ms = 50;
        time_duration td = milliseconds(ms);
        time_duration tdmargin = milliseconds(ms*0.02);

        ptime t1(microsec_clock::local_time());
        boost::this_thread::sleep(td);
        ptime t2(microsec_clock::local_time());

        CHECK(t1 != t2);

        ptime t3(t1+td);
        CHECK_CLOSE(t3, t2, tdmargin);
    }
}
SUITE(testThreadable)
{
    TEST(derivation)
    {
    /*
        shared_ptr<Physics> p (new Physics);
        CHECK(boost::dynamic_pointer_cast<Threadable>(p));
    */
    }
    TEST(threading)
    {
    /*
    */
    }
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
