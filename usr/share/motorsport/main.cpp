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
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
