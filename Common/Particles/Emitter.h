#pragma once

#include "Particle.h"
#include "MasterClock.h"
#include "EmitterController.h"

#include "cinder/Rand.h"
#include "cinder/Easing.h"

/*
 * WITHOUT THE FOLLOWING, IT'S NOT POSSIBLE
 * TO COMPILE OBJECTIVE-C++ WITH GCC
 */

#ifndef Nil
#define Nil __DARWIN_NULL
#endif

#ifndef nil
#define nil __DARWIN_NULL
#endif

namespace chronotext
{
    struct EmitterFunctions
    {
        static float null(float t)
        {
            return 1;
        }
        
        static float linear(float t)
        {
            return t;
        }
        
        static float inverseLinear(float t)
        {
            return 1 - linear(t);
        }
        
        static float easeInQuad(float t)
        {
            return ci::easeInQuad(t);
        }
        
        static float inverseEaseInQuad(float t)
        {
            return 1 - easeInQuad(t);
        }
        
        static float easeOutQuad(float t)
        {
            return ci::easeOutQuad(t);
        }
        
        static float inverseEaseOutQuad(float t)
        {
            return 1 - easeOutQuad(t);
        }
        
        static float sineBell(float t)
        {
            return ci::math<float>::sin(t * M_PI);
        }
        
        static float inverseSineBell(float t)
        {
            return 1 - sineBell(t);
        }
        
        static float expoBell(float t)
        {
            if (t < 0.5)
            {
                return ci::easeOutExpo(t * 2);
            }
            else
            {
                return 1 - ci::easeInExpo(t * 2 - 1);
            }
        }
        
        static float inverseExpoBell(float t)
        {
            return 1 - expoBell(t);
        }
    };
    
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
    
    class Emitter
    {
    public:
        Clock clock;
        ci::Rand random;
        
        EmitterParams params;
        
        EmitterController *controller;
        bool controllerIsOwned;

        EmitterData *data;
        bool dataIsOwned;
        
        ci::Vec2f position;
        std::vector<Sprite*> sprites;
        std::list<Particle> particles;
        
        bool finished;
        bool spawnFinished;
        
        float accum;
        int total;
        
        Emitter(MasterClock *masterClock, const EmitterParams &params);
        ~Emitter();

        void setController(EmitterController *controller, bool controllerIsOwned);
        void setData(EmitterData *data, bool dataIsOwned);

        virtual void update(float dt);
        virtual void draw(const ci::Vec2f &scale);
        
        virtual void addSprite(Sprite *sprite);
        virtual void addParticle(double now);
        
        virtual void accumulateForces();
        virtual void integrate(float dt);
        virtual void satisfyConstraints();
        
        static bool shouldBeRemoved(Emitter *emitter)
        {
            return emitter->finished;
        }
    };
}

namespace chr = chronotext;
