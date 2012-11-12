#include "chronotext/android/cinder/CinderSketchComplex.h"
#include "chronotext/android/cinder/CinderDelegate.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void CinderSketchComplex::enableAccelerometer(float updateFrequency, float filterFactor)
{
	// TODO
}

void CinderSketchComplex::disableAccelerometer()
{
	// TODO
}

int CinderSketchComplex::getWindowWidth()
{
    return ((CinderDelegate*)context)->mWidth;
}

int CinderSketchComplex::getWindowHeight()
{
    return ((CinderDelegate*)context)->mHeight;
}

Vec2f CinderSketchComplex::getWindowSize()
{
    return Vec2f(((CinderDelegate*)context)->mWidth, ((CinderDelegate*)context)->mHeight);
}

float CinderSketchComplex::getWindowAspectRatio()
{
    return ((CinderDelegate*)context)->mWidth / (float)((CinderDelegate*)context)->mHeight;
}

Area CinderSketchComplex::getWindowBounds() const
{
    return Area(0, 0, ((CinderDelegate*)context)->mWidth, ((CinderDelegate*)context)->mHeight);
}

double CinderSketchComplex::getElapsedSeconds()
{
    return 0;
}

uint32_t CinderSketchComplex::getElapsedFrames()
{
    return 0;
}
