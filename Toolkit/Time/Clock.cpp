#include "Clock.h"
#include "MasterClock.h"

using namespace std;

namespace chronotext
{
    Clock::Clock()
    :
    mst(0),
    rate(1),
    state(STOPPED)
    {
        timeBase = new DefaultTimeBase();
        timeBaseIsOwned = true;
    }
    
    Clock::Clock(TimeBase *timeBase)
    :
    timeBase(timeBase),
    timeBaseIsOwned(false),
    mst(0),
    rate(1),
    state(STOPPED)
    {}
    
    Clock::Clock(MasterClock *masterClock)
    :
    timeBaseIsOwned(false),
    mst(0),
    rate(1),
    state(STOPPED)
    {
        timeBase = masterClock->timeBase;
        masterClock->add(this);
    }
    
    Clock::~Clock()
    {
        if (timeBaseIsOwned)
        {
            delete timeBase;
        }
    }
    
    void Clock::start()
    {
        tbst = timeBase->getTime();
        state = STARTED;
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
