#include "MotorsportConfig.h"

MotorsportConfig::MotorsportConfig()
{
    run = false;
}
MotorsportConfig::~MotorsportConfig()
{
}
void MotorsportConfig::setRun(bool run)
{
    this->run = run;
}
bool MotorsportConfig::getRun()
{
    return this->run;
}
