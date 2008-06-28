
#include "Core.h"
#include "Group.h"
#include "Threadable.h"
#include "Exception.h"
#include "Os.h"

namespace motorsport {

/** Core constructor.
\param world the root \ref Group where all groups will be held. */
Core::Core(shared_ptr< Group > world) {
  // Bouml preserved body begin 0001F8E5
    if (!world)
        throw Exception ("Can't create Core, the provided world is not initializated.");
    this->world = world;
  // Bouml preserved body end 0001F8E5
}
/** Default constructor. Creates a Group named "world" as root group.
\sa Group */
Core::Core() {
  // Bouml preserved body begin 0001FCE6
  world.reset(new Group("default world"));
  // Bouml preserved body end 0001FCE6
}
/** Simple destructor. */
Core::~Core() {
  // Bouml preserved body begin 0001F965
  // Bouml preserved body end 0001F965
}

/** Returns the \ref world \ref Group of this core. */
shared_ptr<Group> Core::getWorld() const {
  // Bouml preserved body begin 0001F540
  return world;
  // Bouml preserved body end 0001F540
}

} // namespace motorsport
