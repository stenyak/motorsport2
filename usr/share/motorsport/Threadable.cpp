
#include "Threadable.h"
#include "Exception.h"

namespace motorsport {

/** Changes the thread frequency.
\param frequency the desired new frequency, in Hz. */
void Threadable::setFrequency(float frequency) {
  // Bouml preserved body begin 0001F6D5
  if (frequency <= 0)
      throw Exception ("Can't set a frequency lower or equal to zero.");
  this->frequency = frequency;
  // Bouml preserved body end 0001F6D5
}
/** \returns the \ref frequency at which this thread is trying to run, in Hz. */
float Threadable::getFrequency() const {
  // Bouml preserved body begin 0001F555
  return frequency;
  // Bouml preserved body end 0001F555
}
/** \return true if the thread is not looping.
\return false if the thread is running (looping). */
bool Threadable::isPaused() const {
  // Bouml preserved body begin 0001FAD5
    return paused;
  // Bouml preserved body end 0001FAD5
}
/** \return true if the thread should stop.
\return false if the thread should keep running (looping). */
bool Threadable::hasToStop() const {
  // Bouml preserved body begin 0001F445
    return shouldStop;
  // Bouml preserved body end 0001F445
}
/** Creates a thread and starts running it. No thread should be \ref isCreated created already. The loop is run with the \ref main method of the class.*/
void Threadable::start() {
  // Bouml preserved body begin 0001F955
    {
        mutex::scoped_lock l(mutBthread);
        if (bthread)
            throw Exception("Can't create new thread if it's already created.");

        bthread.reset(new thread(bind(&Threadable::startLoop, this)));
        while (!loopStarted)
            ; //empty
    }
    paused = false;
  // Bouml preserved body end 0001F955
}
/** Resumes the execution of the thread. The thread should be \ref isPaused paused and \ref isCreated created already.*/
void Threadable::resume() {
  // Bouml preserved body begin 0001FA55
    {
        mutex::scoped_lock l(mutBthread);
        if (!bthread)
            throw Exception("Can't resume if thread is not created.");
    }
    if (!isPaused())
        throw Exception("Can't resume if thread is not paused.");
    paused = false;
  // Bouml preserved body end 0001FA55
}
/** Pauses the execution of the thread. The thread should be \ref isCreated created already, and should not be already \ref isPaused paused.*/
void Threadable::pause() {
  // Bouml preserved body begin 0001F8D5
    if (isPaused())
        throw Exception("Can't pause if thread is not running.");
    paused = true;
  // Bouml preserved body end 0001F8D5
}
/** Stops and deletes the thread. The thread should be already \ref isCreated created.*/
void Threadable::stop() {
  // Bouml preserved body begin 0001F9D5
    if (!isPaused())
        pause();
    {
        mutex::scoped_lock l(mutBthread);
        if (!bthread)
            throw Exception("Can't stop if thread is not created.");
        else
        shouldStop = true;
        bthread->join();
        shouldStop = false;
        bthread.reset();
        loopStarted = true;
    }
    //TODO: shouldStop mutex
    //TODO: add all pause and etc. mutex
  // Bouml preserved body end 0001F9D5
}
/** Regular destructor. Calls \ref stop in order to terminate the thread. */
Threadable::~Threadable() {
  // Bouml preserved body begin 0001F7D5
    safeStop();
  // Bouml preserved body end 0001F7D5
}
/** Stops and deletes the thread. The thread doesn't need to be already \ref isCreated created.*/
void Threadable::safeStop() {
  // Bouml preserved body begin 0001F4C5
  // TODO: somehow refactor this with stop(), knowing the mutex can't be taken 2 times.
    if (!isPaused())
        pause();
    {
        mutex::scoped_lock l(mutBthread);
        if (bthread)
        {
            shouldStop = true;
            bthread->join();
            shouldStop = false;
            bthread.reset();
        }
        loopStarted = false;
    }
  // Bouml preserved body end 0001F4C5
}
/** Basic threadable constructor. No thread will be spawned until \ref create is used.
\param frequency the rate at which the thread will try to loop (in Hz). */
Threadable::Threadable(float frequency): frequency(frequency), shouldStop(false), paused(false), loopStarted(false) {
  // Bouml preserved body begin 0001F4D5
  // Bouml preserved body end 0001F4D5
}
/** Executes the \ref main method of the class, then sets "loopStarted" to true.*/
void Threadable::startLoop() {
  // Bouml preserved body begin 0001F545
    loopStarted = true;
    bind(&Threadable::main, this)();
  // Bouml preserved body end 0001F545
}

} // namespace motorsport
