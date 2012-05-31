#pragma once

#include "cinder/app/AppCocoaTouch.h"
#include "cinder/gl/gl.h"
#include "cinder/Timer.h"

class CinderSketch
{
protected:
    void *context;

public:
    enum
    {
        FLAG_FOCUS_GAIN,
        FLAG_FOCUS_LOST,
        FLAG_APP_RESUME,
        FLAG_APP_PAUSE,
        FLAG_SCREEN_ENTER,
        FLAG_SCREEN_LEAVE
    };

    CinderSketch(void *context) : context(context) {}

	virtual void setup() {}
	virtual void shutdown() {}
	virtual void resize(ci::app::ResizeEvent event) {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual void start(int flags) {}
	virtual void stop(int flags) {}
	
	void touchesBegan(ci::app::TouchEvent event);
	void touchesMoved(ci::app::TouchEvent event);
	void touchesEnded(ci::app::TouchEvent event);
	
	virtual void addTouch(int index, float x, float y) {}
	virtual void updateTouch(int index, float x, float y) {}
	virtual void removeTouch(int index, float x, float y) {}

	virtual void accelerated(ci::app::AccelEvent event) {}

	void enableAccelerometer(float updateFrequency = 30, float filterFactor = 0.1f);
	void disableAccelerometer();
	
	int getWindowWidth();
	int getWindowHeight();
    float getContentScale();
    float getWindowAspectRatio();
    ci::Area getWindowBounds() const;

	double getElapsedSeconds();
	uint32_t getElapsedFrames();

	std::ostream& console() { return std::cout; }
};
