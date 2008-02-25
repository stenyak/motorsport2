#include <Sim.h>
#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace boost;
using namespace motorsport_sim;

int main(int argc, char**argv)
{
    shared_ptr<Sim> sim(new Sim());
    cout<< "test" << endl;
    return 0;
}
