#include <string.h>
#include <unittest++/UnitTest++.h>
#include <motorsport/Group.h>
#include <motorsport/Core.h>
#include <motorsport/Exception.h>
using namespace motorsport;
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
using namespace boost;
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;


SUITE(testCore)
{
    TEST(construction)
    {
        CHECK_EQUAL(Core().getWorld()->getId(), "default world");
        shared_ptr<Core> c1 (new Core);
        CHECK_EQUAL(c1->getWorld()->getId(), "default world");
        shared_ptr<Core> c2 (new Core());
        c2->getWorld();
        CHECK_EQUAL(c2->getWorld()->getId(), "default world");

        shared_ptr<Group>g2 (new Group ("test01"));
        shared_ptr<Core> c3(new Core(g2));
        CHECK_EQUAL(c3->getWorld()->getId(), "test01");

        g2.reset();
        CHECK_THROW(shared_ptr<Core> c5(new Core(g2)), Exception);
    }
}
SUITE(testException)
{
    TEST(construction)
    {
        CHECK_THROW(Exception(""), std::exception);
        shared_ptr<Exception> e(new Exception("Basic description"));
        CHECK_EQUAL("Basic description", e->getDescription());
        CHECK_EQUAL("Basic description", e->what());
    }
}
SUITE(testGroup)
{
    TEST(construction)
    {
        Group g2();
        Group g3("test01");
        CHECK_THROW(Group(""), Exception);
        CHECK_THROW(Group("/"), Exception);
        CHECK_THROW(Group("/t"), Exception);
        CHECK_THROW(Group("t/"), Exception);
        CHECK_THROW(Group("t/t"),Exception);

        shared_ptr<Group> g4(new Group("test02"));
        CHECK_EQUAL("test02", g4->getId());
        CHECK_EQUAL("/test02", g4->getGlobalId());

        g4->setId("test03");
        CHECK_EQUAL("test03", g4->getId());
        CHECK_EQUAL("/test03", g4->getGlobalId());

        CHECK_THROW(g4->setId(""), Exception);
        CHECK_THROW(g4->setId("/"), Exception);
        CHECK_THROW(g4->setId("/test04"), Exception);
        CHECK_THROW(g4->setId("test04/"), Exception);

    }
    TEST(children)
    {
        shared_ptr<Group> g5(new Group("test05"));
        shared_ptr<Group> g6(new Group("test06"));
        shared_ptr<Group> g7(new Group("test06")); //same id as g6

        CHECK_THROW(g5->addChild(g5), Exception); //can't add itself
        g5->addChild(g6);
        CHECK_THROW(g5->addChild(g6), Exception); //can't add it 2 times
        CHECK_THROW(g5->addChild(g7), Exception); //can't add id 2 times
        CHECK_EQUAL(g6, g5->getChild("test06"));
        CHECK_THROW(g6->addChild(g5), Exception);

        CHECK_EQUAL("test05", g5->getId());
        CHECK_EQUAL("/test05", g5->getGlobalId());
        CHECK_EQUAL("test06", g6->getId());
        CHECK_EQUAL("/test05/test06", g6->getGlobalId());

        g6->addChild(g7);
        CHECK_EQUAL("/test05/test06/test06", g7->getGlobalId());
        CHECK_THROW(g7->addChild(g5), Exception);

        g6.reset();
        CHECK_THROW(g5->addChild(g6), Exception);
        CHECK_THROW(g5->getChild("unused name"), Exception);
    }
    TEST(reparenting)
    {
        shared_ptr<Group> g8(new Group("test08"));
        shared_ptr<Group> g9(new Group("test09"));
        shared_ptr<Group> g10(new Group("test10"));

        g8->addChild(g9);
        g8->addChild(g10);
        CHECK_EQUAL(g9, g8->getChild("test09"));
        CHECK_EQUAL(g10, g8->getChild("test10"));

        g9->addChild(g10);
        CHECK_EQUAL(g10, g9->getChild("test10"));
        CHECK_THROW(g8->getChild("test10"), Exception);

        shared_ptr<Group> g11(new Group("test11"));
        g11->addChild(g9);
        g8->addChild(g11);
        CHECK_EQUAL("/test08/test11/test09/test10", g10->getGlobalId());
    }
}
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
        UNITTEST_TIME_CONSTRAINT((int)(ms*margin));
        boost::this_thread::sleep(td);
    }
    TEST(sleep2)
    {
        boost::thread make_thread();
        int ms = 500;
        float margin = 1.01;
        time_duration td = milliseconds(ms);
        UNITTEST_TIME_CONSTRAINT((int)(ms*margin));
        boost::this_thread::sleep(td);
    }
    TEST(nowCorrectness)
    {
        boost::thread make_thread();
        int ms = 50;
        float margin = 0.05;
        time_duration td = milliseconds(ms);
        time_duration tdmargin = milliseconds((int)(ms*margin));

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
