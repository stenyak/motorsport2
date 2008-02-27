#include "Motorsport.h"
#include <iostream>

using namespace std;
using namespace stk;

Motorsport::Motorsport(pMotorsportConfig config)
{
    this->config = config;
    log.reset(new Log("Motorsport Simulator"));
}
int Motorsport::start()
{
    int result = 0;
    if (config->getRun())
    {
        log->dev("Motorsport Simulator started.");
    }
    return result;
}

Motorsport::~Motorsport()
{
}
