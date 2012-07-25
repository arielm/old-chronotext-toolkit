#pragma once

#include "FollowablePath.h"

class SplinePath
{
    int size;
    int capacity;
    float tol;
    float (*gamma)(float t, float *in);
    float *x;
    float *y;

    void ensureCapacity(int minCapacity);

public:
    SplinePath(int capacity, float tol, float (*gamma)(float t, float *in));
    ~SplinePath();

    void clear();
    void add(float x, float y);
    void compute(FollowablePath *path);
};

float GammaCatmullRom(float t, float *in);
float GammaBSpline(float t, float *in);
