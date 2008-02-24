
#include "Group.h"

namespace motorsport {

/** Simple constructor.
\param name the name that will be used in its logs. */
Group::Group(const string & name): Loggable(name) {
  // Bouml preserved body begin 0001FAE6
  // Bouml preserved body end 0001FAE6
}
/** Simple destructor. */
Group::~Group() {
  // Bouml preserved body begin 0001FB66
  // Bouml preserved body end 0001FB66
}
/** Changes the \ref parent. */
void Group::setParent(shared_ptr< Group > parent) {
  // Bouml preserved body begin 0001FC66
  this->parent = parent;
  // Bouml preserved body end 0001FC66
}
/** Moves a group to the \ref groups list of this group. The group gets its parent group changed accordingly. */
void Group::addGroup(shared_ptr< Group > group) {
  // Bouml preserved body begin 0001F9E5
  groups.push_back(group);
  group->setParent(shared_from_this());
  // Bouml preserved body end 0001F9E5
}

/** Default constructor, should not be used. */
Group::Group(): Loggable("default name") {
  // Bouml preserved body begin 0001FBE6
  // Bouml preserved body end 0001FBE6
}

} // namespace motorsport
