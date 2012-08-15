#pragma once

#include "Curves.h"

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
        
        float radius0;
        float radius1;
        
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
        
        std::vector<std::string> spritePaths;
        
        EmitterParams()
        :
        gravity(ci::Vec2f::zero()),
        friction(0),
        duration(std::numeric_limits<double>::max()),
        spawnDuration(std::numeric_limits<double>::max()),
        spawnRate(1),
        spawnFunction(Curves::one),
        radius0(0),
        radius1(1),
        direction0(0),
        direction1(360),
        speed0(0),
        speed1(0),
        lifetime0(1),
        lifetime1(1),
        angle0(0),
        angle1(0),
        angularVelocity0(0),
        angularVelocity1(0),
        scale0(1),
        scale1(1),
        scaleFunction(Curves::one),
        alpha0(1),
        alpha1(1),
        alphaFunction(Curves::one),
        mass0(0),
        mass1(0),
        massRelativeToScale(false),
        massFactor(0)
        {}
        
        void addSpritePath(const std::string &path)
        {
            spritePaths.push_back(path);
        }
    };
}

namespace chr = chronotext;
