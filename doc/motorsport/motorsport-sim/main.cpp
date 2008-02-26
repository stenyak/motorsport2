#include <motorsport-sim/Sim.h>
using namespace motorsport_sim;
#include <iostream>
using namespace std;
#include <boost/shared_ptr.hpp>
using namespace boost;

int main(int , char**)
{
    shared_ptr<Sim> sim(new Sim());
    return 0;
}
