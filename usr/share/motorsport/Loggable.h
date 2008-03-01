/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_LOGGABLE_H
#define MOTORSPORT_LOGGABLE_H

#include <string>
using namespace std;

namespace motorsport { class Exception; } 

namespace motorsport {

/** By creating a class derived from this, the class acquires the ability to generate detailed logs. */
class Loggable {
  protected:
    /** Loggable constructor.
    \param string a \ref name that helps identify logs origin. */
    Loggable(const string & id);
    /** Simple destructor. */
    virtual ~Loggable() {};


  public:
    /** \returns a string that helps identify the object in the generated logs. */
    virtual const string getId() const;
    virtual void setId(const string & id);

  private:
    /** A name for the object to be logged. It will help identify where logs came from. */
    string id;

    /** Default constructor. Should not be used. */
    Loggable();

};

} // namespace motorsport
#endif
