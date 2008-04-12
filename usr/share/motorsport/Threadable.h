/** Copyright (C) 2008 Motorsport Project contributors (see license.txt) */
#ifndef MOTORSPORT_THREADABLE_H
#define MOTORSPORT_THREADABLE_H

#include <boost/shared_ptr.hpp>
using namespace boost;
#include <boost/thread.hpp>
using namespace boost;
#include <boost/bind.hpp>
using namespace boost;

namespace motorsport { class Exception; } 

namespace motorsport {

/** Allows a class to be runnable in a separate thread. */
class Threadable {
  public:
    /** Changes the thread frequency.
    \param frequency the desired new frequency, in Hz. */
    void setFrequency(float frequency);
    /** \returns the \ref frequency at which this thread is trying to run, in Hz. */
    float getFrequency() const;
    /** \return true if the thread is not looping.
    \return false if the thread is running (looping). */
    bool isPaused() const;
    /** \return true if this class has already spawned a thread.
    \return false if no thread has been created yet. */
    bool isCreated() const;
    /** Creates a thread and starts running it. No thread should be \ref isCreated created already. The loop is run with the \ref operator() functor method of the class.*/
    void start();
    /** Resumes the execution of the thread. The thread should be \ref isPaused paused and \ref isCreated created already.*/
    void resume();
    /** Pauses the execution of the thread. The thread should be \ref isCreated created already, and should not be already \ref isPaused paused.*/
    void pause();
    /** Stops and deletes the thread. The thread should be already \ref isCreated created.*/
    void stop();
    /** Regular destructor. Calls \ref stop in order to terminate the thread. */
    virtual ~Threadable();

  protected:
    /** Basic threadable constructor. No thread will be spawned until \ref create is used.
    \param frequency the rate at which the thread will try to loop (in Hz). */
    Threadable(float frequency);
    /** Functor method, contains the actual code of the thread. Should be implemented by all derived classes. The method must implement two things:
    1: Check for \ref hasToStop regularly. As soon as it's true, the functor method must exit.
    2: Check for isPaused(). If it's true, the functor method should stop doing things, until it becomes false again. Sleeps should be used while waiting. */
    virtual void operator()() = 0;

  private:
    /** Default constructor, should not be used. */
    Threadable();
    /** The frequency (in Hz) at which the thread will attempt to run its main loop.*/
    float frequency;
    /** False if the currently running thread should be stopped and deleted. */
    bool hasToStop;
    /** True if the currently running thread should be paused. */
    bool paused;
    /** Holds data related to the boost::thread. */
    shared_ptr<thread> bthread;
};

} // namespace motorsport
#endif
