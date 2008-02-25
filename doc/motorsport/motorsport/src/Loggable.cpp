
#include "Loggable.h"

namespace motorsport {

/** \returns a string that helps identify the object in the generated logs. */
const string Loggable::getName() const {
  // Bouml preserved body begin 0001F8E6
  return name;
  // Bouml preserved body end 0001F8E6
}

/** Loggable constructor.
\param string a \ref name that helps identify logs origin. */
Loggable::Loggable(const string & name): name(name) {
  // Bouml preserved body begin 0001FA66
  // Bouml preserved body end 0001FA66
}

/** Default constructor. Should not be used. */
Loggable::Loggable() {
  // Bouml preserved body begin 0001F966
  name = "default name";
  // Bouml preserved body end 0001F966
}


} // namespace motorsport
