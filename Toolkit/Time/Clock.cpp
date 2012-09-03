#include "Clock.h"
#include "MasterClock.h"

using namespace std;

namespace chronotext
{
    Clock::Clock()
    :
    timeBaseIsOwned(true),
    master(NULL),
    mst(0),
    rate(1),
    state(STOPPED)
    {
        timeBase = new DefaultTimeBase();
    }
    
    Clock::Clock(TimeBase *timeBase)
    :
    timeBase(timeBase),
    timeBaseIsOwned(false),
    master(NULL),
    mst(0),
    rate(1),
    state(STOPPED)
    {}
    
    Clock::Clock(MasterClock *masterClock)
    :
    timeBase(masterClock->timeBase),
    timeBaseIsOwned(false),
    master(masterClock),
    mst(0),
    rate(1),
    state(STOPPED)
    {
        masterClock->add(this);
    }
    
    Clock::~Clock()
    {
        if (timeBaseIsOwned)
        {
            delete timeBase;
        }
        
        if (master)
        {
            master->remove(this);
        }
    }
    
    void Clock::start()
    {
        tbst = timeBase->getTime();
        state = STARTED;
    }
    
    void Clock::restart()
    {
        mst = 0;
        start();
    }
    
    void Clock::stop()
    {
        if (state != STOPPED)
        {
            mst = getTime();
            state = STOPPED;
        }
    }
    
    double Clock::getTime()
    {
        return mst + ((state == STOPPED) ? 0 : (timeBase->getTime() - tbst) * rate);
    }
    
    void Clock::setTime(int now)
    {
        mst = now;
    }
    
    int Clock::getState()
    {
        return state;
    }
    
    void Clock::setRate(double factor)
    {
        rate = factor;
    }
}
