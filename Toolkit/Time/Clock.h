/*
 * INSPIRED BY javax.media.Clock
 */

#pragma once

#include "DefaultTimeBase.h"

namespace chronotext
{
    class MasterClock;

    class Clock : public TimeBase
    {
        double mst;
        double rate;
        int state;
        double tbst;

        TimeBase *timeBase;
        bool timeBaseIsOwned;
        
    public:
        enum
        {
            STOPPED,
            STARTED
        };

        Clock();
        Clock(TimeBase *timeBase);
        Clock(MasterClock *masterClock);
        
        ~Clock();
        
        void start();
        void stop();
        double getTime();
        void setTime(int now);
        int getState();
        void setRate(double factor);
    };
}
