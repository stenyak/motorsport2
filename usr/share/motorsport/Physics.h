/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_PHYSICS_H
#define MOTORSPORT_PHYSICS_H

#include "Threadable.h"

namespace motorsport {


class Physics : public Threadable {
  public:
    Physics(float frequency);
    virtual ~Physics();

  private:
    virtual void operator()();
    Physics();
};

} // namespace motorsport
#endif
