#pragma once

#include "cinder/Rand.h"
#include "cinder/Easing.h"

/*
 * THE FOLLOWING IS NECESSARY IN ORDER TO
 * KEEP-ON COMPILING OBJECTIVE-C++ WITH GCC
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
}

namespace chr = chronotext;
