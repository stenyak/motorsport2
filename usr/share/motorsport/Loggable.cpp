
#include "motorsport/Loggable.h"
#include "motorsport/Exception.h"

namespace motorsport {

/** Loggable constructor.
\param string a \ref name that helps identify logs origin. */
Loggable::Loggable(const string & id) {
  // Bouml preserved body begin 0001FA66
  setId(id);
  // Bouml preserved body end 0001FA66
}
/** \returns a string that helps identify the object in the generated logs. */
const string Loggable::getId() const {
  // Bouml preserved body begin 0001F8E6
    return id;
  // Bouml preserved body end 0001F8E6
}

void Loggable::setId(const string & id) {
  // Bouml preserved body begin 0001F4A3
    if (id == "")
        throw Exception("Can't set the id, it must not be empty.");

    this->id = id;
  // Bouml preserved body end 0001F4A3
}
/** Default constructor. Should not be used. */
Loggable::Loggable() {
  // Bouml preserved body begin 0001F966
    throw Exception("Must not use default Loggable() constructor.");
  // Bouml preserved body end 0001F966
}

} // namespace motorsport
