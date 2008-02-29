/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_EXCEPTION_H
#define MOTORSPORT_EXCEPTION_H

#include <string>
using namespace std;
#include <exception>
using namespace std;

namespace motorsport {


class Exception : public exception {
  public:
    /** Simple constructor.
    \param description a \ref description of the exception. */
    Exception(const string & description);
    /** Simple destructor. */
    virtual ~Exception() throw();
    /** Returns a \ref description of the exception. */
    virtual const string & getDescription() const;
    /** Returns a \ref description of the exception. */
    virtual const char * what() const throw(/**/);

  private:
    /** Description of the exception. */
    string description;
};

} // namespace motorsport
#endif
