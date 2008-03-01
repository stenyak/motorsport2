/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_CORE_H
#define MOTORSPORT_CORE_H


#include <boost/shared_ptr.hpp>
using namespace boost;

namespace motorsport { class Group; } 
namespace motorsport { class Exception; } 

namespace motorsport {

/** The main component of Motorsport. In theory, several can be created and used simultaneous and independently. However, usually only one is used for each program. */
class Core {
  public:
    /** Core constructor.
    \param world the root \ref Group where all groups will be held. */
    Core(shared_ptr< Group > world);
    /** Default constructor. Creates a Group named "world" as root group.
    \sa Group */
    Core();

    /** Simple destructor. */
    virtual ~Core();

    /** Returns the \ref world \ref Group of this core. */
    virtual shared_ptr<Group> getWorld() const;

  protected:
    /** Root group of the simulated world. */
    shared_ptr<Group> world;

};

} // namespace motorsport
#endif
