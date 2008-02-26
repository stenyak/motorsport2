/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_LOGGABLE_H
#define MOTORSPORT_LOGGABLE_H

#include <string>
using namespace std;

namespace motorsport {

/** By creating a class derived from this, the class acquires the ability to generate detailed logs. */
class Loggable {
  public:
    /** \returns a string that helps identify the object in the generated logs. */
    virtual const string getName() const;
    /** Returns an string with some debug information about the loggable object. */
    virtual const string debugStr(int indent = 0) const;

  protected:
    /** Loggable constructor.
    \param string a \ref name that helps identify logs origin. */
    Loggable(const string & name);

    /** Simple destructor. */
    virtual ~Loggable() {};

    /** A name for the object to be logged. It will help identify where logs came from. */
    string name;


  private:
    /** Default constructor. Should not be used. */
    Loggable();

};

} // namespace motorsport
#endif
