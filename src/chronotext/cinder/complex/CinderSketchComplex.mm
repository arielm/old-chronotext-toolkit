#include "chronotext/cinder/complex/CinderSketchComplex.h"

#import "chronotext/cinder/complex/CinderRenderDelegate.h"

using namespace ci;
using namespace app;
using namespace std;

void CinderSketchComplex::touchesBegan(TouchEvent event)
{
	for (vector<TouchEvent::Touch>::const_iterator it = event.getTouches().begin(); it != event.getTouches().end(); ++it)
	{
		float x = it->getX();
		float y = it->getY();
		addTouch(it->getId() - 1, x, y);
	}
}

void CinderSketchComplex::touchesMoved(TouchEvent event)
{
	for (vector<TouchEvent::Touch>::const_iterator it = event.getTouches().begin(); it != event.getTouches().end(); ++it)
	{
		float x = it->getX();
		float y = it->getY();
		updateTouch(it->getId() - 1, x, y);
	}
}

void CinderSketchComplex::touchesEnded(TouchEvent event)
{
	for (vector<TouchEvent::Touch>::const_iterator it = event.getTouches().begin(); it != event.getTouches().end(); ++it)
	{
		float x = it->getX();
		float y = it->getY();
		removeTouch(it->getId() - 1, x, y);
	}
}

void CinderSketchComplex::enableAccelerometer(float updateFrequency, float filterFactor)
{
	[(CinderRenderDelegate*)context setAccelFilterFactor:filterFactor];
	
	if (updateFrequency <= 0)
	{
		updateFrequency = 30;
	}
	
	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:(1 / updateFrequency)];
	[[UIAccelerometer sharedAccelerometer] setDelegate:(CinderRenderDelegate*)context];
}

void CinderSketchComplex::disableAccelerometer()
{
	[[UIAccelerometer sharedAccelerometer] setDelegate:nil];
}

int CinderSketchComplex::getWindowWidth()
{
    return ((CinderRenderDelegate*)context).width;
}

int CinderSketchComplex::getWindowHeight()
{
    return ((CinderRenderDelegate*)context).height;
}

Vec2f CinderSketchComplex::getWindowSize()
{
    return Vec2f(((CinderRenderDelegate*)context).width, ((CinderRenderDelegate*)context).height);
}

float CinderSketchComplex::getContentScale()
{
    return ((CinderRenderDelegate*)context).contentScale;
}

float CinderSketchComplex::getWindowAspectRatio()
{
    return ((CinderRenderDelegate*)context).width / (float)((CinderRenderDelegate*)context).height;
}

Area CinderSketchComplex::getWindowBounds() const
{
    return Area(0, 0, ((CinderRenderDelegate*)context).width, ((CinderRenderDelegate*)context).height);
}

double CinderSketchComplex::getElapsedSeconds()
{
    return ((CinderRenderDelegate*)context).elapsedSeconds;
}

uint32_t CinderSketchComplex::getElapsedFrames()
{
    return ((CinderRenderDelegate*)context).elapsedFrames;
}
