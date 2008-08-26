/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_PHYSICS_H
#define MOTORSPORT_PHYSICS_H

#include "Threadable.h"
#include <boost/shared_ptr.hpp>
using namespace boost;
#include <btBulletDynamicsCommon.h>

namespace motorsport {

/** Implementation of physics engine. */
class Physics : public Threadable {
  public:
    /** Simple constructor. */
    Physics(float frequency);
    /** Simple destructor. */
    virtual ~Physics();
    /** Physics loop method. TODO: make protected.*/
    void main();

  private:
    shared_ptr<btRigidBody> fallRigidBody;
    shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
};

} // namespace motorsport
#endif
