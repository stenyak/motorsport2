#include <string.h>
#include <unittest++/UnitTest++.h>
#include <motorsport/Group.h>
#include <motorsport/Exception.h>
using namespace motorsport;
#include <boost/shared_ptr.hpp>
using namespace boost;

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
    TEST(debugging)
    {
        shared_ptr<Group> world(new Group("test01"));
        CHECK_EQUAL("test01", world->getId());
    }
    TEST(construction)
    {
        shared_ptr<Group> world(new Group("test01"));
        CHECK_EQUAL("test01", world->getId());
        CHECK_EQUAL("/test01", world->getGlobalId());

        world->setId("test02");
        CHECK_EQUAL("test02", world->getId());
        CHECK_EQUAL("/test02", world->getGlobalId());

        CHECK_THROW(world->setId(""), Exception);
        CHECK_THROW(world->setId("/"), Exception);
        CHECK_THROW(world->setId("/test02"), Exception);
        CHECK_THROW(world->setId("test02/"), Exception);

        CHECK_THROW(Group(""), Exception);
        CHECK_THROW(Group("/"), Exception);
        CHECK_THROW(Group("/t"), Exception);
        CHECK_THROW(Group("t/"), Exception);
        CHECK_THROW(Group("t/t"),Exception);
    }
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
