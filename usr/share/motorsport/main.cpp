#include <string.h>
#include <unittest++/UnitTest++.h>
#include <motorsport/Group.h>
#include <motorsport/Exception.h>
using namespace motorsport;
#include <exception>

TEST(group)
{
    shared_ptr<Group> world(new Group("test01"));
    CHECK_EQUAL("test01", world->getId());
    CHECK_EQUAL("/test01", world->getGlobalId());
    world->setId("test02");
    CHECK_EQUAL("test02", world->getId());
    CHECK_EQUAL("/test02", world->getGlobalId());
    CHECK_THROW(world->setId(""), Exception);
    CHECK_THROW(Group(""), Exception);
    CHECK_THROW(Group("/"), Exception);
    CHECK_THROW(Group("/t"), Exception);
    CHECK_THROW(Group("t/"), Exception);
    CHECK_THROW(Group("t/t"),Exception);
    CHECK_THROW(world->setId("/"), Exception);
    CHECK_THROW(world->setId("/test02"), Exception);
    CHECK_THROW(world->setId("test02/"), Exception);
}
int main (int, char*[])
{
    return UnitTest::RunAllTests();
}
