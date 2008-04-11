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
