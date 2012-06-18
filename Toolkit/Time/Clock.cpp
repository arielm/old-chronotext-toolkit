#include "Clock.h"

#include <stdexcept>

using namespace chronotext;
using namespace std;

Clock::Clock()
:
mst(0),
rate(1),
state(STOPPED)
{
    timeBase = new DefaultTimeBase();
    timeBaseIsDefault = true;
}

Clock::Clock(TimeBase *timeBase)
:
timeBase(timeBase),
timeBaseIsDefault(false),
mst(0),
rate(1),
state(STOPPED)
{}

Clock::~Clock()
{
  if (timeBaseIsDefault)
  {
      delete timeBase;
  }
}

void Clock::start()
{
    if (state != STOPPED)
    {
        throw runtime_error("MEDIA CLOCK: CLOCK ALREADY STARTED");
    }
    
    tbst = timeBase->getTime();
    state = STARTED;
}

void Clock::stop()
{
    if (state != STOPPED)
    {
        mst = getMediaTime();
        state = STOPPED;
    }
}

double Clock::getMediaTime()
{
    return mst + ((state == STOPPED) ? 0 : (timeBase->getTime() - tbst) * rate);
}

void Clock::setMediaTime(int now)
{
    if (state != STOPPED)
    {
        throw runtime_error("MEDIA CLOCK: CLOCK ALREADY STARTED");
    }
    
    mst = now;
}

int Clock::getState()
{
    return state;
}

void Clock::setRate(double factor)
{
    if (state != STOPPED)
    {
        throw runtime_error("MEDIA CLOCK: CLOCK ALREADY STARTED");
    }
    
    rate = factor;
}
