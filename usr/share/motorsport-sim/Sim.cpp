
#include "motorsport-sim/Sim.h"
#include "motorsport/Core.h"

#include <motorsport/Group.h>
using namespace motorsport;
#include <iostream.h>
using namespace std;
namespace motorsport_sim {

/** Default constructor. Instantiates a Motorsport \ref Core amongst other things.  */
Sim::Sim() {
  // Bouml preserved body begin 0001FD66
    shared_ptr<Group> world(new Group("world"));
    shared_ptr<Group> v1(new Group("vehicle"));
    shared_ptr<Group> w1(new Group("wheel1"));
    shared_ptr<Group> w2(new Group("wheel2"));
    shared_ptr<Group> w3(new Group("wheel3"));
    shared_ptr<Group> w4(new Group("wheel4"));
    shared_ptr<Group> v2(new Group("vehicle2"));
    shared_ptr<Group> a1(new Group("area1"));
    world->addGroup(v1);
    world->addGroup(v2);
    world->addGroup(a1);
    v1->addGroup(w1);
    v1->addGroup(w2);
    v1->addGroup(w3);
    v1->addGroup(w4);
    v2->addGroup(w1);
    a1->addGroup(v1);
    world->removeGroup(v2);
    core.reset(new Core(world));
    cout<< world->debugStr()<< endl;
  // Bouml preserved body end 0001FD66
}
/** Simple destructor. */
Sim::~Sim() {
  // Bouml preserved body begin 0001FDE6
  // Bouml preserved body end 0001FDE6
}

} // namespace motorsport_sim
