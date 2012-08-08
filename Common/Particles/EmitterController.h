#pragma once

namespace chronotext
{
    class Emitter;
    
    class EmitterController
    {
    public:
        virtual ~EmitterController() {}

        virtual void emitterWillUpdate(Emitter *emitter, float dt, double now) {}
        virtual void emitterIsFinished(Emitter *emitter) {}
    };
}    

namespace chr = chronotext;
