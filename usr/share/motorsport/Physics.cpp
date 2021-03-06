
#include "Physics.h"
#include "Os.h"

namespace motorsport {

/** Simple constructor. */
Physics::Physics(float frequency): Threadable(frequency) {
  // Bouml preserved body begin 0001F755
/*
//TODO: move this, or the necessary part, to UML and groups
    btAxisSweep3* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btCollisionShape* groundShape;
    btCollisionShape* fallShape;
    btDefaultMotionState* groundMotionState;
    btRigidBody* groundRigidBody;
    btDefaultMotionState* fallMotionState;
*/
    // Build the broadphase
    int maxProxies = 1024;
    btVector3 worldAabbMin(-10000,-10000,-10000);
    btVector3 worldAabbMax(10000,10000,10000);
    broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);
    // Set up the collision configuration and dispatcher
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    // The actual physics solver
    solver = new btSequentialImpulseConstraintSolver;
    // The world.
    dynamicsWorld = (new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration));
    // Do_everything_else_here ///////////////////////////////
    dynamicsWorld->setGravity(btVector3(0,-10,0));
    groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
    fallShape = new btSphereShape(1);
    groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);
    fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
    btScalar mass = 1;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
    fallRigidBody = (new btRigidBody(fallRigidBodyCI));
    dynamicsWorld->addRigidBody(fallRigidBody);
    //Collada converter initialization
    colladaConverter = new ColladaConverter(dynamicsWorld);
    
  // Bouml preserved body end 0001F755
}
/** Simple destructor. */
Physics::~Physics() {
  // Bouml preserved body begin 0001F855
    safeStop(); //this has to be always run as first line of destructor FIXME
    dynamicsWorld->removeRigidBody(fallRigidBody);
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;
    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete dynamicsWorld;
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;
    delete fallShape;
    delete groundShape;
    // Clean up behind ourselves like good little programmers
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
    delete colladaConverter;
  // Bouml preserved body end 0001F855
}
/** Physics loop method. TODO: make protected.*/
void Physics::main() {
  // Bouml preserved body begin 0001F46A
    time_duration period = microseconds((long int)(1000000./getFrequency()));
    time_duration halfperiod = microseconds((long int)(500000./getFrequency()));
    ptime lasttime, currtime;
    lasttime = microsec_clock::local_time();
    time_duration zero = lasttime - lasttime;
    while (!hasToStop())
    {
        if (isPaused())
        {
            boost::this_thread::sleep(period); //TODO: modify API to allow a simple resume or a restart (forgetting the passed time)
        }
        else
        {
            currtime = microsec_clock::local_time(); 
            time_duration dt = currtime - lasttime;
            const bool substepping = true;
            const int substeps = 100;
            if (substepping)
            {
                int stepsInc = dynamicsWorld->stepSimulation(dt.total_microseconds()/1000000.,substeps,1./getFrequency());
                steps += stepsInc;
                lasttime += period * stepsInc;
            }
            else
            {
                while (dt > halfperiod) //TODO: merge this loop with the parent, so that the thread can be pauses if physics get under realtime.
                {
                    ++steps;
                    dynamicsWorld->stepSimulation(1./getFrequency(),0);
                    dt -= period;
                    lasttime += period;
                }
            }
            boost::this_thread::sleep(halfperiod); //FIXME: profile previous loop, and adjust sleep accordingly on the fly
        }
    }
    btTransform trans;
    fallRigidBody->getMotionState()->getWorldTransform(trans);
    //std::cout<<"<< Finished "<<steps<<" steps at "<<getFrequency()<< " Hz. Final position: "<< trans.getOrigin().getY() << std::endl;
  // Bouml preserved body end 0001F46A
}
/** Loads the desired dae file (.dae) with pathname relative to Motorsport data directory. */
void Physics::loadCollada(string filename) {
  // Bouml preserved body begin 0001FC40
    filename = motorsport::Os::getDataPath(filename);
    colladaConverter->load(filename.c_str());
  // Bouml preserved body end 0001FC40
}

} // namespace motorsport
