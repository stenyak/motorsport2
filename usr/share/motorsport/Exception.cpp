
#include "motorsport/Exception.h"

namespace motorsport {

/** Simple constructor.
\param description a \ref description of the exception. */
Exception::Exception(const string & description): description(description) {
  // Bouml preserved body begin 0001F523
  // Bouml preserved body end 0001F523
}
/** Simple destructor. */
Exception::~Exception() throw() {
  // Bouml preserved body begin 0001F623
  // Bouml preserved body end 0001F623
}
/** Returns a \ref description of the exception. */
const char * Exception::what() const throw() {
  // Bouml preserved body begin 0001F5A3
  return description.c_str();
  // Bouml preserved body end 0001F5A3
}

} // namespace motorsport
