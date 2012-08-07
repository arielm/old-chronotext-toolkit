#pragma once

#include "Sprite.h"

namespace chronotext
{
    struct Particle
    {
        Sprite *sprite;
        
        ci::Vec2f position;
        ci::Vec2f previousPosition;
        ci::Vec2f acceleration;
        
        double creationTime;
        double lifetime;
        
        float mass;
        
        float angle; // IN DEGREES
        float angle0; // IN DEGREES
        float angularVelocity; // IN DEGREES PER SECOND
        
        float scale;
        float scale0;
        float (*scaleFunction)(float t);
        
        float alpha;
        float alpha0;
        float (*alphaFunction)(float t);
        
        bool remove;
        
        Particle(Sprite *sprite, const ci::Vec2f &position, const ci::Vec2f &velocity, double creationTime, double lifetime, float mass, float angle0, float angularVelocity, float scale0, float (*scaleFunction)(float t), float alpha0, float (*alphaFunction)(float t))
        :
        sprite(sprite),
        position(position),
        previousPosition(position - velocity),
        creationTime(creationTime),
        lifetime(lifetime),
        mass(mass),
        angle0(angle0),
        angularVelocity(angularVelocity),
        scale0(scale0),
        scaleFunction(scaleFunction),
        alpha0(alpha0),
        alphaFunction(alphaFunction),
        remove(false)
        {}
        
        static bool shouldBeRemoved(const Particle &particle)
        {
            return particle.remove;
        }
    };
}

namespace chr = chronotext;
