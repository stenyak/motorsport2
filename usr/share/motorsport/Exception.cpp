
#include "motorsport/Exception.h"

namespace motorsport {

/** Simple constructor.
\param description a \ref description of the exception. */
Exception::Exception(const string & description): description(description) {
  // Bouml preserved body begin 0001F523
    if (description == "")
        throw std::exception();
  // Bouml preserved body end 0001F523
}
/** Simple destructor. */
Exception::~Exception() throw() {
  // Bouml preserved body begin 0001F623
  // Bouml preserved body end 0001F623
}
/** Returns a \ref description of the exception. Like \ref what , but using std::strings instead. */
const string & Exception::getDescription() const {
  // Bouml preserved body begin 0001F440
    return description;
  // Bouml preserved body end 0001F440
}
/** Returns a \ref description of the exception. \sa getDescription*/
const char * Exception::what() const throw(/**/) {
  // Bouml preserved body begin 0001F5A3
  return description.c_str();
  // Bouml preserved body end 0001F5A3
}

} // namespace motorsport
