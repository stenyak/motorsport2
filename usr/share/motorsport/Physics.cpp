
#include "Physics.h"

namespace motorsport {

/** Simple constructor. */
Physics::Physics(float frequency): Threadable(frequency) {
  // Bouml preserved body begin 0001F755
  // Bouml preserved body end 0001F755
}
/** Simple destructor. */
Physics::~Physics() {
  // Bouml preserved body begin 0001F855
  // Bouml preserved body end 0001F855
}
/** Physics loop method. */
void Physics::operator()() {
  // Bouml preserved body begin 0001F46A
    int count = 0;
    int paused= 0;
    while (!hasToStop())
    {
        if (isPaused())
        {
            ++paused;
        }
        else
        {
            ++count;
        }
    }
    std::cout<<"<< Finished a loop at "<<getFrequency()<< " Hz. Stepped "<< count<< " times. Paused "<< paused<< " times."<< std::endl;
  // Bouml preserved body end 0001F46A
}

} // namespace motorsport
