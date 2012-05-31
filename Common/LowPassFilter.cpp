#include "LowPassFilter.h"

#include <math.h>

#define kAccelerometerMinStep 0.02
#define kAccelerometerNoiseAttenuation 3.0

static double Norm(double x, double y, double z)
{
    return sqrt(x * x + y * y + z * z);
}

static double Clamp(double v, double min, double max)
{
    if (v > max)
    {
        return max;
    }
    
    if (v < min)
    {
        return min;
    }
    
    return v;
}

void LowPassFilter::start(float sampleRate, float cutoffFrequency, bool adaptive)
{
    x = y = z = 0;
    
    double dt = 1.0 / sampleRate;
    double RC = 1.0 / cutoffFrequency;
    
    filterConstant = dt / (dt + RC);
}

void LowPassFilter::addAcceleration(float ax, float ay, float az)
{
    double alpha = filterConstant;
    
    if (adaptive)
    {
        double d = Clamp(fabs(Norm(x, y, z) - Norm(ax, ay, az)) / kAccelerometerMinStep - 1.0, 0.0, 1.0);
        alpha = (1.0 - d) * filterConstant / kAccelerometerNoiseAttenuation + d * filterConstant;
    }
    
    x = ax * alpha + x * (1.0 - alpha);
    y = ay * alpha + y * (1.0 - alpha);
    z = az * alpha + z * (1.0 - alpha);
}
