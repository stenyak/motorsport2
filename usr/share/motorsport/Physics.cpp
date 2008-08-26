
#include "Physics.h"

namespace motorsport {

/** Simple constructor. */
Physics::Physics(float frequency): Threadable(frequency) {
  // Bouml preserved body begin 0001F755
    // Build the broadphase
    int maxProxies = 1024;
    btVector3 worldAabbMin(-10000,-10000,-10000);
    btVector3 worldAabbMax(10000,10000,10000);
    btAxisSweep3* broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);
    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    // The world.
    dynamicsWorld.reset(new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration));
    // Do_everything_else_here ///////////////////////////////
    dynamicsWorld->setGravity(btVector3(0,-10,0));
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
    btCollisionShape* fallShape = new btSphereShape(1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);
    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
    btScalar mass = 1;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
    fallRigidBody.reset(new btRigidBody(fallRigidBodyCI));
    dynamicsWorld->addRigidBody(&(*fallRigidBody));
  // Bouml preserved body end 0001F755
}
/** Simple destructor. */
Physics::~Physics() {
  // Bouml preserved body begin 0001F855
/*/ UNCOMMENT ME
    dynamicsWorld->removeRigidBody(*fallRigidBody);
    delete fallRigidBody->getMotionState();
    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;
    delete fallShape;
    delete groundShape;
    // Clean up behind ourselves like good little programmers
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
/*/
  // Bouml preserved body end 0001F855
}
/** Physics loop method. TODO: make protected.*/
void Physics::main() {
  // Bouml preserved body begin 0001F46A
    int count = 0;
    int paused= 0;
    while (!hasToStop())
    {
        if (isPaused())
        {
            ++paused;
        }
        else
        {
            //dynamicsWorld->stepSimulation(0.01,100,0.01);
            //dynamicsWorld->stepSimulation(1/getFrequency(),0);
            ++count;
        }
        if (count >= 1000 || paused >= 1000) break;
    }
    btTransform trans;
    fallRigidBody->getMotionState()->getWorldTransform(trans);
    std::cout << "Final position: "<< count << ", " << trans.getOrigin().getY() << std::endl;
    std::cout<<"<< Finished a loop at "<<getFrequency()<< " Hz. Stepped "<< count<< " times. Paused "<< paused<< " times."<< std::endl;
  // Bouml preserved body end 0001F46A
}

} // namespace motorsport
