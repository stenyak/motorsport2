#include <Core.h>
#include <Group.h>
#include <iostream>
using namespace std;
using namespace motorsport;

int main(int argc, char**argv)
{
    shared_ptr<Group> world(new Group("world"));
    shared_ptr<Group> vehicle(new Group("vehicle"));
    world->addGroup(vehicle);
    shared_ptr<Core> core(new Core(world));
    cout<< world->getName()<< endl;
    cout<< vehicle->getName()<< endl;
    return 0;
}
