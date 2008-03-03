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
    virtual ~Sim();

  protected:
    /** The Motorsport core used for this simulation. */
    shared_ptr<motorsport::Core> core;

  public:
    virtual shared_ptr<motorsport::Core> getCore() const;
};

} // namespace motorsport_sim
#endif
