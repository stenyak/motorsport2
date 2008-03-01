#include <string.h>
#include <unittest++/UnitTest++.h>
#include <motorsport/Group.h>
#include <motorsport/Core.h>
#include <motorsport/Exception.h>
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
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
