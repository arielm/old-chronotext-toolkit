#include "CinderSketch.h"

#import "CinderRenderDelegate.h"

using namespace ci;
using namespace app;
using namespace std;

void CinderSketch::touchesBegan(TouchEvent event)
{
	for (vector<TouchEvent::Touch>::const_iterator it = event.getTouches().begin(); it != event.getTouches().end(); ++it)
	{
		float x = it->getX();
		float y = it->getY();
		addTouch(it->getId() - 1, x, y);
	}
}

void CinderSketch::touchesMoved(TouchEvent event)
{
	for (vector<TouchEvent::Touch>::const_iterator it = event.getTouches().begin(); it != event.getTouches().end(); ++it)
	{
		float x = it->getX();
		float y = it->getY();
		updateTouch(it->getId() - 1, x, y);
	}
}

void CinderSketch::touchesEnded(TouchEvent event)
{
	for (vector<TouchEvent::Touch>::const_iterator it = event.getTouches().begin(); it != event.getTouches().end(); ++it)
	{
		float x = it->getX();
		float y = it->getY();
		removeTouch(it->getId() - 1, x, y);
	}
}

void CinderSketch::enableAccelerometer(float updateFrequency, float filterFactor)
{
	[(CinderRenderDelegate*)context setAccelFilterFactor:filterFactor];
	
	if (updateFrequency <= 0)
	{
		updateFrequency = 30;
	}
	
	[[UIAccelerometer sharedAccelerometer] setUpdateInterval:(1 / updateFrequency)];
	[[UIAccelerometer sharedAccelerometer] setDelegate:(CinderRenderDelegate*)context];
}

void CinderSketch::disableAccelerometer()
{
	[[UIAccelerometer sharedAccelerometer] setDelegate:nil];
}

int CinderSketch::getWindowWidth()
{
    return ((CinderRenderDelegate*)context).width;
}

int CinderSketch::getWindowHeight()
{
    return ((CinderRenderDelegate*)context).height;
}

float CinderSketch::getContentScale()
{
    return ((CinderRenderDelegate*)context).contentScale;
}

float CinderSketch::getWindowAspectRatio()
{
    return ((CinderRenderDelegate*)context).width / (float)((CinderRenderDelegate*)context).height;
}

Area CinderSketch::getWindowBounds() const
{
    return Area(0, 0, ((CinderRenderDelegate*)context).width, ((CinderRenderDelegate*)context).height);
}

double CinderSketch::getElapsedSeconds()
{
    return ((CinderRenderDelegate*)context).elapsedSeconds;
}

uint32_t CinderSketch::getElapsedFrames()
{
    return ((CinderRenderDelegate*)context).elapsedFrames;
}
