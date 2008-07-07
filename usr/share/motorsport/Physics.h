/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_PHYSICS_H
#define MOTORSPORT_PHYSICS_H

#include "Threadable.h"

namespace motorsport {

/** Implementation of physics engine. */
class Physics : public Threadable {
  public:
    /** Simple constructor. */
    Physics(float frequency);
    /** Simple destructor. */
    virtual ~Physics();

  protected:
    /** Physics loop method. */
    void main();
};

} // namespace motorsport
#endif
