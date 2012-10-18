#pragma once

namespace chronotext
{
    class Emitter;
    
    class EmitterController
    {
    public:
        virtual ~EmitterController() {}

        virtual void emitterWillUpdate(Emitter *emitter, float dt, double now) {}
        virtual void emitterHasEnded(Emitter *emitter) {}
    };
}    

namespace chr = chronotext;
