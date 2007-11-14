#ifndef MOTORSPORT_H_
#define MOTORSPORT_H_

#include <log.h>
#include <boost/shared_ptr.hpp>
using namespace boost;

class Motorsport;
/** Shared pointer to Motorsport object.*/
typedef shared_ptr<Motorsport> pMotorsport;  

/** Motorsport Simulator core class.
In order to start the simulation, first an instance has to be created using the \ref Motorsport::Motorsport "constructor", providing appropriate \ref Options "configuration options". Finally, its \ref start method has to be called. \sa main */
class Motorsport
{
  public:
    /** Motorsport options handler. Provides a way to store, modify and pass options sets around. See \ref Motorsport::Options source code for default initializations.*/  
    class Options
    {
      public:
        /** Setter function for \ref run. \sa getRun */
        void setRun(bool run);
        /** Getter function for \ref run. \sa setRun */
        bool getRun();
        /** Motorsport Options constructor. */
        Options();
        /** Motorsport Options destructor. */
        ~Options();
      private:
        /** Sets whether the simulation should run or not when \ref Motorsport::start is invoked. */
        bool run;   
    };
    /** Shared pointer to \ref Motorsport::Options object. */
    typedef shared_ptr<Options> pOptions;
    /** Starts the simulation.
    @returns 0 on sucess
    @returns other values on error */
	int start();
	/** Constructs a Motorsport Simulator object.
	@ref options the simulator options. */
    Motorsport(pOptions options);
    /** Motorsport Simulator destructor. */
	virtual ~Motorsport();
  private:
    /** Holds simulation options for this instance of \ref Motorsport. */
    pOptions options;
    /** Private constructor, without any options. Should not be called. TODO find out how to prevent its execution. Make it virtual or whatever... */
    Motorsport();
    stk::pLog log;
};

#endif /*MOTORSPORT_H_*/
