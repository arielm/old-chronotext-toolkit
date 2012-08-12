#pragma once

#include "Particle.h"
#include "MasterClock.h"
#include "EmitterFunctions.h"
#include "EmitterController.h"

namespace chronotext
{
    struct EmitterParams
    {
        ci::Vec2f gravity;
        float friction;
        
        double duration;
        double spawnDuration;
        
        float spawnRate; // NEW PARTICLES PER SECOND - BASED ON DT
        float (*spawnFunction)(float t);
        
        /*
         * IN DEGREES
         */
        float direction0;
        float direction1;
        
        /*
         * IN PIXELS PER SECOND
         */
        float speed0;
        float speed1;
        
        double lifetime0;
        double lifetime1;
        
        /*
         * IN DEGREES
         */
        float angle0;
        float angle1;
        
        /*
         * IN DEGREES PER SECOND
         */
        float angularVelocity0;
        float angularVelocity1;
        
        float scale0;
        float scale1;
        float (*scaleFunction)(float t);
        
        float alpha0;
        float alpha1;
        float (*alphaFunction)(float t);
        
        float mass0;
        float mass1;
        
        bool massRelativeToScale;
        float massFactor;
        
        EmitterParams()
        :
        gravity(ci::Vec2f::zero()),
        friction(0),
        duration(std::numeric_limits<double>::max()),
        spawnDuration(std::numeric_limits<double>::max()),
        spawnRate(1),
        spawnFunction(EmitterFunctions::null),
        direction0(0),
        direction1(360),
        speed0(1),
        speed1(1),
        lifetime0(1),
        lifetime1(1),
        angle0(0),
        angle1(0),
        angularVelocity0(0),
        angularVelocity1(0),
        scale0(1),
        scale1(1),
        scaleFunction(EmitterFunctions::null),
        alpha0(1),
        alpha1(1),
        alphaFunction(EmitterFunctions::null),
        mass0(0),
        mass1(0),
        massRelativeToScale(false),
        massFactor(0)
        {}
    };
    
    class EmitterData
    {
    public:
        virtual ~EmitterData() {}
    };
    
    typedef boost::shared_ptr<class Emitter> EmitterRef;

    class Emitter
    {
    protected:
        Clock clock;
        ci::Rand random;
        
        EmitterParams params;
        
        EmitterController *controller;
        bool controllerIsOwned;
        
        EmitterData *data;
        bool dataIsOwned;
        
        std::vector<Sprite*> sprites;
        std::list<Particle> particles;
        
        bool finished;
        bool spawnFinished;
        
        float accum;
        int total;
        
    public:
        ci::Vec2f position;

        Emitter(MasterClock *masterClock, const EmitterParams &params, uint32_t seed = 214);
        ~Emitter();

        virtual void setController(EmitterController *controller, bool controllerIsOwned);
        virtual void setData(EmitterData *data, bool dataIsOwned);
        
        virtual EmitterData* getData();
        virtual bool isFinished();

        virtual void update(float dt);
        virtual void draw(const ci::Vec2f &scale);
        
        virtual void addSprite(Sprite *sprite);
        virtual void addParticle(double now);
        
        virtual void accumulateForces();
        virtual void integrate(float dt);
        virtual void satisfyConstraints();
        
        static bool emitterShouldBeRemoved(EmitterRef emitter)
        {
            return emitter->isFinished();
        }
    };
}

namespace chr = chronotext;
