
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
/** \return true if this class has already spawned a thread.
\return false if no thread has been created yet. */
bool Threadable::isCreated() const {
  // Bouml preserved body begin 0001FB55
    return bthread;
  // Bouml preserved body end 0001FB55
}
/** Creates a thread and starts running it. No thread should be \ref isCreated created already. The loop is run with the \ref operator() functor method of the class.*/
void Threadable::start() {
  // Bouml preserved body begin 0001F955
    if (isCreated())
        throw Exception("Can't create new thread if it's already created.");
    paused = false;
    bthread.reset(new thread(bind(&Threadable::operator(), this)));
  // Bouml preserved body end 0001F955
}
/** Resumes the execution of the thread. The thread should be \ref isPaused paused and \ref isCreated created already.*/
void Threadable::resume() {
  // Bouml preserved body begin 0001FA55
    if (!isCreated())
        throw Exception("Can't resume if thread is not created.");
    if (!isPaused())
        throw Exception("Can't resume if thread is not paused.");
    //TODO: protect pause from multi threads
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
    if (!isCreated())
        throw Exception("Can't stop if thread is not created.");
    if (!isPaused())
        pause();
    hasToStop = true;
    bthread->join();
    bthread.reset();
    hasToStop = false;
  // Bouml preserved body end 0001F9D5
}
/** Regular destructor. Calls \ref stop in order to terminate the thread. */
Threadable::~Threadable() {
  // Bouml preserved body begin 0001F7D5
    stop();
  // Bouml preserved body end 0001F7D5
}
/** Basic threadable constructor. No thread will be spawned until \ref create is used.
\param frequency the rate at which the thread will try to loop (in Hz). */
Threadable::Threadable(float frequency): frequency(frequency), hasToStop(false) {
  // Bouml preserved body begin 0001F4D5
  // Bouml preserved body end 0001F4D5
}

} // namespace motorsport
