#include <time.h>
#include <vector.h>
using namespace std;
#include <boost/shared_ptr.hpp>
using namespace boost;
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
        int stopResult;
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
    pthread_join(thread, NULL);

    isPaused = true;

    return stopResult;
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
    const int nDiffs = 100;
    Time::time diffs[nDiffs];
    for (int i=0; i<nDiffs; ++i) diffs[i] = 0;
    //int nSlow = 0;
    while (e->isActive)
    {
        if (e->isPaused) Time::sleep(0.1);
        else
        {
            wallTime = Time::now();
            /*
            for (int i=0; i<nDiffs-1; i++)
            {
                if (diffs[i+1] < diffs[i]) ++nSlow;
                diffs[i] = diffs[i+1];
            }
            if (nSlow > 0)
            {
                cout << "Running slower than real time"<< endl;
            }
            nSlow = 0;
            */
            while ( (wallTime > e->virtualTime) && (e->isActive) && (!e->isPaused) )
            {
                e->runFunction();
                e->virtualTime += e->period;
            }
            flush(cout);
            Time::sleep( e->period );
        }
    }
    e->stopResult = result;
    pthread_exit(0);
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

    long double freq = 1e100;
    shared_ptr<EngineThread> graphic (new EngineThread(freq, computeGraphic, physicsBuffer, graphicsBuffer));
    shared_ptr<EngineThread> physic  (new EngineThread(freq, computePhysic, physicsBuffer, nullBuffer));
    shared_ptr<EngineThread> sound  (new EngineThread(freq, computeSound, physicsBuffer, nullBuffer));

    physic->start();
    sound->start();
    graphic->start();
    Time::sleep (5);
    if ( graphic->stop() ) result = -1;
    if ( physic->stop()  ) result = -1;
    if ( sound->stop()  ) result = -1;


    cout << endl;
    return result;
}

