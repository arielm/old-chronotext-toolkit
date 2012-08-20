#pragma once

#include "Curves.h"

namespace chronotext
{
    typedef std::pair<float, float> RandomRange;
    
    struct EmitterParams
    {
        ci::Vec2f gravity;
        float friction;
        bool positionLocked;

        /*
         * IF EQUAL TO std::numeric_limits<double>::max(), THE SYSTEM WILL NEVER END
         */
        double duration;
        
        /*
         * - IF EQUAL TO std::numeric_limits<double>::max(), spawnRate PARTICLES-PER-SECOND WILL BE EMITTED UNTIL THE SYSTEM ENDS
         * - IF EQUAL TO std::numeric_limits<double>::min(), spawnRate PARTICLES WILL BE EMITTED IN ONE SHOT
         * - IN BOTH CASES, spawnCurve WILL BE IGNORED
         */
        double spawnDuration;
        
        float spawnRate; // NEW PARTICLES PER SECOND
        chr::Curve spawnCurve;

        RandomRange lifetime;
        RandomRange radius;
        RandomRange direction; // IN DEGREES
        RandomRange speed; // IN PIXELS PER SECOND
        RandomRange angle; // IN DEGREES
        RandomRange angularVelocity; // IN DEGREES PER SECOND
        
        RandomRange scale;
        chr::Curve scaleCurve;
        
        RandomRange alpha;
        chr::Curve alphaCurve;
        
        RandomRange mass;
        bool massRelativeToScale;
        float massFactor;
        
        std::vector<std::string> spritePaths;
        
        EmitterParams()
        :
        gravity(ci::Vec2f::zero()),
        friction(0),
        positionLocked(true),
        duration(std::numeric_limits<double>::max()),
        spawnDuration(std::numeric_limits<double>::max()),
        spawnRate(1),
        spawnCurve(chr::CurveOne()),
        radius(std::make_pair(0, 0)),
        direction(std::make_pair(0, 360)),
        speed(std::make_pair(0, 0)),
        lifetime(std::make_pair(1, 1)),
        angle(std::make_pair(0, 0)),
        angularVelocity(std::make_pair(0, 0)),
        scale(std::make_pair(1, 1)),
        scaleCurve(chr::CurveOne()),
        alpha(std::make_pair(1, 1)),
        alphaCurve(chr::CurveOne()),
        mass(std::make_pair(0, 0)),
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
