#pragma once

#include "DefaultTimeBase.h"

namespace chronotext
{
    class Clock
    {
        enum
        {
            STOPPED,
            STARTED
        };

        int mst;
        double rate;
        int state;
        double tbst;

        TimeBase *timeBase;
        bool timeBaseIsDefault;
        
    public:
        Clock();
        Clock(TimeBase *timeBase);
        
        ~Clock();
        
        void start();
        void stop();
        double getMediaTime();
        void setMediaTime(int now);
        int getState();
        void setRate(double factor);
    };
}
