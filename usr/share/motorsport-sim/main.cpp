#include <boost/shared_ptr.hpp>
using namespace boost;
#include <motorsport/Group.h>
#include <motorsport/Core.h>
#include <motorsport/Exception.h>
using namespace motorsport;
#include "Sim.h"
using namespace motorsport_sim;

int main(int , char**)
{
    shared_ptr<Sim> sim(new Sim());
    return 0;
}
