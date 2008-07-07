#include <unittest++/UnitTest++.h>
#include <boost/shared_ptr.hpp>
using namespace boost;
#include <motorsport/Group.h>
#include <motorsport/Core.h>
#include <motorsport/Exception.h>
using namespace motorsport;
#include <motorsport-sim/Sim.h>
#include <motorsport-sim/Graphics.h>
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
    TEST(graphics)
    {
        shared_ptr<Graphics> g1 (new Graphics(40.0));
        // At this point, there should be a window on the screen.
        g1->loadCollada("beyron.dae");
        //g1->loadCollada("Messerschmitt KR200.dae");
        //g1->loadCollada("bristol/bristol test.dae");
        //g1->loadCollada("LancerEX/Mitsubishi Lancer Evo X.dae");
        //g1->loadCollada("FF430/FF430.dae");
        //g1->loadCollada("Phoenix/Phoenix City Square.dae");
        //ag->loadCollada("shopping center.dae");

        //FIXME: should be able to use start()
        //g1->start();
        //boost::this_thread::sleep(seconds(10));
        //FIXME: make operator() protected once i fix start() crash in nvidia drivers
        (*g1)();
        CHECK_EQUAL(false, g1->isPaused());
    }
}

int main(int , char**)
{
    return UnitTest::RunAllTests();
}

