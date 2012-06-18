/*
 * INSPIRED BY javax.media.Clock
 */

#pragma once

#include "DefaultTimeBase.h"

namespace chronotext
{
    class Clock
    {
        double mst;
        double rate;
        int state;
        double tbst;

        TimeBase *timeBase;
        bool timeBaseIsDefault;
        
    public:
        enum
        {
            STOPPED,
            STARTED
        };

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
