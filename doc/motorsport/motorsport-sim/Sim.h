/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_SIM_SIM_H
#define MOTORSPORT_SIM_SIM_H

#include <boost/shared_ptr.hpp>
using namespace boost;

namespace motorsport { class Core; } 

namespace motorsport_sim {

/** Motorsport Simulation main class. */
class Sim {
  public:
    /** Default constructor. Instantiates a Motorsport \ref Core amongst other things.  */
    Sim();
    /** Simple destructor. */
    ~Sim();

  protected:
    /** The Motorsport core used for this simulation. */
    shared_ptr<motorsport::Core> core;
};

} // namespace motorsport_sim
#endif
