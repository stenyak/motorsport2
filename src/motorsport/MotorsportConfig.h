#ifndef MOTORSPORTCONFIG_H_
#define MOTORSPORTCONFIG_H_

#include <boost/shared_ptr.hpp>
using namespace boost;

class MotorsportConfig;
/** Shared pointer to \ref Motorsport::Options object. */
typedef shared_ptr<MotorsportConfig> pMotorsportConfig;
/** Motorsport options handler. Provides a way to store, modify and pass options sets around. See \ref Motorsport::Options source code for default initializations.*/  
class MotorsportConfig
{
  public:
    /** Setter function for \ref run. \sa getRun */
    void setRun(bool run);
    /** Getter function for \ref run. \sa setRun */
    bool getRun();
    /** Motorsport Options constructor. */
    MotorsportConfig();
    /** Motorsport Options destructor. */
    ~MotorsportConfig();
  private:
    /** Sets whether the simulation should run or not when \ref Motorsport::start is invoked. */
    bool run;   
};
#endif /*MOTORSPORTCONFIG_H_*/
