#include <string.h>
#include <unittest++/UnitTest++.h>
#include <motorsport/Group.h>
#include <motorsport/Core.h>
#include <motorsport/Exception.h>
#include <motorsport/Physics.h>
#include <motorsport/Os.h>
using namespace motorsport;
#include <boost/shared_ptr.hpp>
using namespace boost;

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

        Group gg2();

        shared_ptr<Group>g2 (new Group ("test01"));
        shared_ptr<Core> c3(new Core(g2));
        CHECK_EQUAL(c3->getWorld()->getId(), "test01");

        g2.reset();
        CHECK_THROW(shared_ptr<Core> c5(new Core(g2)), Exception);
    }
}
SUITE(testPhysics)
{
    TEST(physics)
    {
        shared_ptr<Physics> p4 (new Physics(300.0));
        shared_ptr<Physics> p5 (new Physics(100.0));
        shared_ptr<Physics> p6 (new Physics(60.0));
        shared_ptr<Physics> p7 (new Physics(30.0));
        //std::cout<<p4->getNodeListString()<<std::endl;
        //p4->loadCollada("beyron.dae");
        //std::cout<<p4->getNodeListString()<<std::endl;

        p4->start();
        p5->start();
        p6->start();
        p7->start();
        boost::this_thread::sleep(seconds(1));
        p4->stop();
        p5->stop();
        p6->stop();
        p7->stop();
        std::cout<<std::endl;
        p4->start();
        p5->start();
        p6->start();
        p7->start();
        boost::this_thread::sleep(seconds(1));
        p4->stop();
        p5->stop();
        p6->stop();
        p7->stop();
        std::cout<<std::endl;
        p4->start();
        p5->start();
        p6->start();
        p7->start();
        boost::this_thread::sleep(seconds(1));
        p4->stop();
        p5->stop();
        p6->stop();
        p7->stop();
        std::cout<<std::endl;
        p4->start();
        p5->start();
        p6->start();
        p7->start();
        boost::this_thread::sleep(seconds(1));
        p4->stop();
        p5->stop();
        p6->stop();
        p7->stop();
        std::cout<<std::endl;

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
        CHECK_THROW(Group("t/t/t"),Exception);

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
        float margin = 1.05;
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
    TEST(construction)
    {
        shared_ptr<Physics> p0 (new Physics(102.0));
        CHECK(boost::dynamic_pointer_cast<Threadable>(p0));
        CHECK_EQUAL(102, p0->getFrequency());
    }
    TEST(modification)
    {
        shared_ptr<Physics> p1 (new Physics(101.0));
        CHECK_EQUAL(101, p1->getFrequency());

        p1->setFrequency(201);
        CHECK_EQUAL(201, p1->getFrequency());
        p1->setFrequency(10001);
        CHECK_EQUAL(10001, p1->getFrequency());
        CHECK_THROW(p1->setFrequency(0), Exception);
        CHECK_EQUAL(10001, p1->getFrequency());
        CHECK_THROW(p1->setFrequency(-100), Exception);
        CHECK_EQUAL(10001, p1->getFrequency());
    }
    TEST(threading)
    {
        shared_ptr<Physics> p2 (new Physics(200.0));
        p2->start();
        p2.reset();

        shared_ptr<Physics> p3 (new Physics(100.0));
        //thread is not created, initiated in non-paused mode
        CHECK_EQUAL(false, p3->isPaused());

        CHECK_THROW(p3->resume(), Exception); //can't resume if thread is not created
        CHECK_EQUAL(false, p3->isPaused()); //still not paused

        p3->start(); //creates thread
        CHECK_EQUAL(false, p3->isPaused());
        CHECK_THROW(p3->start(), Exception); //can't create if thread is already created
        CHECK_EQUAL(false, p3->isPaused());

        p3->pause(); //pauses thread loop
        CHECK_EQUAL(true, p3->isPaused());
        CHECK_THROW(p3->pause(), Exception); //can't pause if thread is not created
        CHECK_EQUAL(true, p3->isPaused());

        p3->resume(); //continues thread loop
        CHECK_EQUAL(false, p3->isPaused());
        CHECK_THROW(p3->resume(), Exception); //can't resume if thread is not paused
        CHECK_EQUAL(false, p3->isPaused());

        p3->stop(); //deletes thread
        CHECK_EQUAL(true, p3->isPaused());
        CHECK_THROW(p3->stop(), Exception); //can't delete if thread is not started
        CHECK_EQUAL(true, p3->isPaused());
        
        p3->start();
        p3->pause();
        p3->stop();
        p3->start();
        //TODO: check loops get executed at right freq.
    }
}
SUITE(testOs)
{
    TEST(paths)
    {
        CHECK_EQUAL(true, motorsport::Os::isFileReadable("run.sh"));
        CHECK_EQUAL(false, motorsport::Os::isFileReadable("wontexist.sh"));

        CHECK_THROW(motorsport::Os::getCfgPath(""),Exception);
        CHECK_THROW(motorsport::Os::getCfgPath("wontexist"),Exception);
        CHECK_EQUAL("usr/share/motorsport-sim-tests/cfg/.hgempty",motorsport::Os::getCfgPath(".hgempty"));

        CHECK_THROW(motorsport::Os::getLogsPath(""),Exception);
        CHECK_THROW(motorsport::Os::getLogsPath("wontexist"),Exception);
        CHECK_EQUAL("usr/share/motorsport-sim-tests/logs/.hgempty",motorsport::Os::getLogsPath(".hgempty"));

        CHECK_THROW(motorsport::Os::getDataPath(""),Exception);
        CHECK_THROW(motorsport::Os::getDataPath("wontexist"),Exception);
        CHECK_EQUAL("usr/share/motorsport-sim-tests/data/.hgempty",motorsport::Os::getDataPath(".hgempty"));
    }
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
