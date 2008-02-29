
#include "motorsport/Core.h"
#include "motorsport/Group.h"

namespace motorsport {

/** Core constructor.
\param world the root \ref Group where all groups will be held. */
Core::Core(shared_ptr< Group > world): world(world) {
  // Bouml preserved body begin 0001F8E5
  shared_ptr<Group> w (new Group("world"));
  world = w;
  // Bouml preserved body end 0001F8E5
}
/** Simple destructor. */
Core::~Core() {
  // Bouml preserved body begin 0001F965
  // Bouml preserved body end 0001F965
}

/** Default constructor. Should not be used. */
Core::Core() {
  // Bouml preserved body begin 0001FCE6
  // Bouml preserved body end 0001FCE6
}


} // namespace motorsport
