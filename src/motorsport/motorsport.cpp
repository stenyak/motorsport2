#include "motorsport.h"
//#include <log/log.h>
#include <iostream>

using namespace std;
//using namespace stk;

Motorsport::Options::Options()
{
    run = false;
}
Motorsport::Options::~Options()
{
}
void Motorsport::Options::setRun(bool run) {this->run = run; }
bool Motorsport::Options::getRun(        ) {return this->run;}
Motorsport::Motorsport(Motorsport::pOptions options)
{
    this->options = options;
}
int Motorsport::start()
{
    int result = 0;
    if (options->getRun())
    {
        cout<< "Running Motorsport!"<< endl;
    }
    //  Log *l = new Log();
    //  delete l;
    return result;
}

Motorsport::~Motorsport()
{
}
