#pragma once

#include "chronotext/texture/Sprite.h"
#include "chronotext/maths/Curves.h"

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
        
        float angle0; // IN DEGREES
        float angularVelocity; // IN DEGREES PER SECOND

        float scale0;
        chr::Curve scaleCurve;
        
        float alpha0;
        chr::Curve alphaCurve;
        
        float angle;
        float scale;
        float alpha;
        
        bool remove;
        
        Particle(Sprite *sprite, const ci::Vec2f &position, const ci::Vec2f &velocity, double creationTime, double lifetime, float mass, float angle0, float angularVelocity, float scale0, chr::Curve scaleCurve, float alpha0, chr::Curve alphaCurve)
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
        scaleCurve(scaleCurve),
        alpha0(alpha0),
        alphaCurve(alphaCurve),
        remove(false)
        {}
        
        static bool shouldBeRemoved(const Particle &particle)
        {
            return particle.remove;
        }
    };
}

namespace chr = chronotext;
