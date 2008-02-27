/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_CORE_H
#define MOTORSPORT_CORE_H


#include <boost/shared_ptr.hpp>
using namespace boost;

namespace motorsport { class Group; } 

namespace motorsport {

/** The main component of Motorsport. In theory, several can be created and used simultaneous and independently. However, usually only one is used in a program. */
class Core {
  public:
    /** Core constructor.
    \param world the root \ref Group where all groups will be held. */
    Core(shared_ptr< Group > world);
    /** Simple destructor. */
    ~Core();


  protected:
    /** Root group of the simulated world. */
    shared_ptr<Group> world;


  private:
    /** Default constructor. Should not be used. */
    Core();

};

} // namespace motorsport
#endif
