#include <unittest++/UnitTest++.h>
#include <boost/shared_ptr.hpp>
using namespace boost;
#include <motorsport/Group.h>
#include <motorsport/Core.h>
#include <motorsport/Exception.h>
using namespace motorsport;
#include "Sim.h"
using namespace motorsport_sim;

SUITE(testSim)
{
    TEST(construction)
    {
        shared_ptr<Sim> sim(new Sim());
        shared_ptr<Core> core(sim->getCore());
        CHECK(core);
        shared_ptr<Group> world(core->getWorld());
        CHECK(world);
        CHECK_EQUAL(world->getId(),"default world");
    }
}
int main(int , char**)
{
    return UnitTest::RunAllTests();
}
