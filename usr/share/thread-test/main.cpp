#include <time.h>
#include <vector.h>
using namespace std;
#include <boost/shared_ptr.hpp>
using namespace boost;
namespace Time
{
    typedef long double time;
    time now()
    {
        Time::time result = 0;

        time_t rawtime;
        ::time(&rawtime);

        tm rawtime2;
        localtime_r(&rawtime, &rawtime2);

        timespec ts;
        if (0 != clock_gettime(CLOCK_REALTIME, &ts)) result = 0;
        else
        {
            result += (long double)(ts.tv_sec);
            result += (long double)(ts.tv_nsec) / (long double)(1000000000);
        }
        return result;
    }
}
class Object
{
    public:
        string getId() {return id;}
        void syncTo(shared_ptr<Object> object) { object->id = id; }
    private:
        string id;
};
// START OF buffer class ////////////////////////////////////////////////////////
class Buffer
{
    public:
        Buffer ();
        ~Buffer();
        void addObject    (shared_ptr<Object> object);
        shared_ptr<Object> getObject    (shared_ptr<Object> object);
        void removeObject (shared_ptr<Object> object);
        void syncTo (shared_ptr<Buffer> buffer);
    private:
        vector< shared_ptr<Object> >::iterator getObjectIterator(shared_ptr<Object> object);
        vector< shared_ptr<Object> >::iterator getObjectIteratorById(string id);
        vector< shared_ptr<Object> > objects;
};
Buffer::Buffer() {}
Buffer::~Buffer(){}
void Buffer::addObject (shared_ptr<Object> object)
{
    if (!getObject(object))
    {
        objects.push_back(object);
    }
}
shared_ptr<Object> Buffer::getObject (shared_ptr<Object> object)
{
    shared_ptr<Object> result;

    vector< shared_ptr<Object> >::iterator it = getObjectIterator(object);
    if (it != objects.end())
        result = *it;

    return result;
}
void Buffer::removeObject (shared_ptr<Object> object)
{
    //TODO
    //if (getObject(object))
        //objects.
    object->getId();
}
void Buffer::syncTo (shared_ptr<Buffer> buffer)
{
    if (!buffer) return;
    vector< shared_ptr<Object> >::iterator bIt;
    for (bIt = buffer->objects.begin(); bIt != buffer->objects.end(); bIt++)
    {
        vector< shared_ptr<Object> >::iterator it;
        it = getObjectIteratorById( (*bIt)->getId() );
        if (it != objects.end())
            if (*it)
                (*it)->syncTo(*bIt);
    }
}
vector< shared_ptr<Object> >::iterator Buffer::getObjectIterator(shared_ptr<Object> object)
{
    vector< shared_ptr<Object> >::iterator result = objects.end();

    vector< shared_ptr<Object> >::iterator it;
    for (it = objects.begin(); it != objects.end(); it++)
        if (*it == object) result = it;

    return result;
}
vector< shared_ptr<Object> >::iterator Buffer::getObjectIteratorById(string id)
{
    vector< shared_ptr<Object> >::iterator result = objects.end();

    vector< shared_ptr<Object> >::iterator it;
    for (it = objects.begin(); it != objects.end(); it++)
        if ((*it)->getId() == id) result = it;

    return result;
}
// END OF buffer clas ///////////////////////////////////////////////////////////

// START OF engine thread class /////////////////////////////////////////////////
class EngineThread
{
    public:
        void start();
        void pause();
        void resume();
        int stop();
        EngineThread (long double frequency, int (*function)(shared_ptr<Buffer> buffer, double seconds), shared_ptr<Buffer> buffer, shared_ptr<Buffer> doubleBuffer);
        ~EngineThread ();
    private:
        void runFunction();

        bool isActive;
        bool isPaused;
        Time::time period;
        Time::time virtualTime;
        int (*function)(shared_ptr<Buffer> buffer, double seconds);
        shared_ptr<Buffer> buffer;
        shared_ptr<Buffer> doubleBuffer;

        pthread_t thread;
        static void* engineThread (void* parameter);
};
EngineThread::EngineThread(long double frequency, int (*function)(shared_ptr<Buffer> buffer, double seconds), shared_ptr<Buffer> buffer, shared_ptr<Buffer> doubleBuffer)
: isActive(true), isPaused(true), period((long double)(1.0)/frequency), virtualTime(Time::now()), function(function), buffer(buffer), doubleBuffer(doubleBuffer)
{
    pthread_create (&thread, NULL, engineThread, (void*)this);
}
EngineThread::~EngineThread()
{
    stop();
}
void EngineThread::start()  { virtualTime = Time::now(); resume(); }
void EngineThread::pause()  { isPaused = true;  }
void EngineThread::resume() { isPaused = false; }
int  EngineThread::stop()
{
    isActive = false;
    int result = 0;
    void *ptrResult = (void*) (&result);

    pthread_join(thread, &ptrResult);
    isPaused = true;

    return result;
}
void EngineThread::runFunction()
{
    if (doubleBuffer) function(buffer, period);
    else
    {
        buffer->syncTo(doubleBuffer);
        function(doubleBuffer, period);
    }
}
void* EngineThread::engineThread(void* parameter)
{
    int result = 0;
    EngineThread * e = (EngineThread*) parameter;

    cout << "Starting an engine at "<< (1/e->period) << "Hz (" << e->period << ")." << endl;
    Time::time wallTime = Time::now();
    while (e->isActive)
    {
        if (e->isPaused) usleep((int)(0.1*1000000));
        else
        {
            wallTime = Time::now();
            while ( (wallTime > e->virtualTime) && (e->isActive) && (!e->isPaused) )
            {
                static Time::time lastDiff;
                e->runFunction();
                e->virtualTime += e->period;
                lastDiff = wallTime - e->virtualTime;
            }
            flush(cout);
            usleep( (unsigned int)(e->period * 1000000.0) );
        }
    }
    int * ptrResult = new int(result);
    pthread_exit((void*)ptrResult);
}
// END OF engine thread class ///////////////////////////////////////////////////

#include <iostream.h>
using namespace std;
int computePhysic(shared_ptr<Buffer>, double seconds){cout<<"."; seconds=0; return 0;}
int computeGraphic(shared_ptr<Buffer>, double seconds){cout<<"G"; seconds=0; return 0;}
int computeSound(shared_ptr<Buffer>, double seconds){cout<<"m"; seconds=0; return 0;}
int main(int argc, char* argv[])
{
    int result = argc* **argv *0;
    cout.precision(70);
    cout.setf(ios::fixed,ios::floatfield);

    shared_ptr<Buffer> physicsBuffer (new Buffer());
    shared_ptr<Buffer> graphicsBuffer(new Buffer());
    shared_ptr<Buffer> nullBuffer;

    shared_ptr<EngineThread> graphic (new EngineThread(60, computeGraphic, physicsBuffer, graphicsBuffer));
    shared_ptr<EngineThread> physic  (new EngineThread(100, computePhysic, physicsBuffer, nullBuffer));
    shared_ptr<EngineThread> sound  (new EngineThread(20, computeSound, physicsBuffer, nullBuffer));

    physic->start();
    sound->start();
    usleep(1*1000000);
    graphic->start();
    usleep(2*1000000);
    graphic->pause();
    usleep(2*1000000);
    graphic->resume();
    usleep(2*1000000);
    graphic->stop();
    usleep(2*1000000);
    graphic->start();
    usleep(1*1000000);
    if ( graphic->stop() ) result = -1;
    usleep ((unsigned int)(0.5*1000000.0));
    if ( physic->stop()  ) result = -1;
    if ( sound->stop()  ) result = -1;


    cout << endl;
    return result;
}

