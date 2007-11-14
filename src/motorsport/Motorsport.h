#ifndef MOTORSPORT_H_
#define MOTORSPORT_H_

#include <log.h>
#include <boost/shared_ptr.hpp>
#include "motorsportConfig.h"
using namespace boost;

class Motorsport;
/** Shared pointer to Motorsport object.*/
typedef shared_ptr<Motorsport> pMotorsport;  

/** Motorsport Simulator core class.
In order to start the simulation, first an instance has to be created using the \ref Motorsport::Motorsport "constructor", providing appropriate \ref Options "configuration options". Finally, its \ref start method has to be called. \sa main */
class Motorsport
{
  public:
    /** Starts the simulation.
    @returns 0 on sucess
    @returns other values on error */
	int start();
	/** Constructs a Motorsport Simulator object.
	@ref options the simulator options. */
    Motorsport(pMotorsportConfig config);
    /** Motorsport Simulator destructor. */
	virtual ~Motorsport();
  private:
    /** Holds simulation options for this instance of \ref Motorsport. */
    pMotorsportConfig config;
    /** Private constructor, without any options. Should not be called. TODO find out how to prevent its execution. Make it virtual or whatever... */
    Motorsport();
    stk::pLog log;
};

#endif /*MOTORSPORT_H_*/
