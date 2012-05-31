#pragma once

/*
 * BASED ON APPLE'S AccelerometerGraph CODE-SAMPLE
 */

class LowPassFilter
{
    double filterConstant;
    bool adaptive;

public:
    float x, y, z;
    
    void start(float sampleRate, float cutoffFrequency, bool adaptive);
    void addAcceleration(float ax, float ay, float az);
};
