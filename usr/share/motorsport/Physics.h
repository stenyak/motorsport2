/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_PHYSICS_H
#define MOTORSPORT_PHYSICS_H

#include "Threadable.h"
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
    btRigidBody* fallRigidBody;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btAxisSweep3* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btCollisionShape* groundShape;
    btCollisionShape* fallShape;
    btDefaultMotionState* groundMotionState;
    btRigidBody* groundRigidBody;
    btDefaultMotionState* fallMotionState;
};

} // namespace motorsport
#endif
