
#include "Sim.h"
#include "../motorsport/Core.h"

#include <motorsport/Group.h>
using namespace motorsport;
#include <iostream.h>
using namespace std;
namespace motorsport_sim {

/** Default constructor. Instantiates a Motorsport \ref Core amongst other things.  */
Sim::Sim() {
  // Bouml preserved body begin 0001FD66
    shared_ptr<Group> world(new Group("default world"));
    core.reset(new Core(world));
  // Bouml preserved body end 0001FD66
}
/** Simple destructor. */
Sim::~Sim() {
  // Bouml preserved body begin 0001FDE6
    core.reset();
  // Bouml preserved body end 0001FDE6
}
shared_ptr<motorsport::Core> Sim::getCore() const {
  // Bouml preserved body begin 0001F44D
    return core;
  // Bouml preserved body end 0001F44D
}

} // namespace motorsport_sim
