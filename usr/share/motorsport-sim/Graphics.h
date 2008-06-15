/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_SIM_GRAPHICS_H
#define MOTORSPORT_SIM_GRAPHICS_H

#include "../motorsport/Threadable.h"

namespace motorsport_sim {

/** Implementation of graphics engine. Takes care of displaying the virtual world on screen. */
class Graphics : public motorsport::Threadable {
  public:
    Graphics(float frequency);
    virtual ~Graphics();

  protected:
    void operator()();
};

} // namespace motorsport_sim
#endif
