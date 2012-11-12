#pragma once

#include "cinder/app/AppAndroid.h"

class CinderSketchComplex
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

	CinderSketchComplex(void *context) : context(context) {}
	virtual ~CinderSketchComplex() {}

	virtual void setup(bool renewContext) {}
	virtual void shutdown() {}
	virtual void resize(ci::app::ResizeEvent event) {}
	virtual void update() {}
	virtual void draw() {}

	virtual void start(int flags) {}
	virtual void stop(int flags) {}

	virtual void addTouch(int index, float x, float y) {}
	virtual void updateTouch(int index, float x, float y) {}
	virtual void removeTouch(int index, float x, float y) {}
    
	virtual void accelerated(ci::app::AccelEvent event) {}
    
	void enableAccelerometer(float updateFrequency = 30, float filterFactor = 0.1f);
	void disableAccelerometer();
	
	int getWindowWidth();
	int getWindowHeight();
    ci::Vec2f getWindowSize();
    float getContentScale() { return 1; }
    float getWindowAspectRatio();
    ci::Area getWindowBounds() const;
    
	double getElapsedSeconds();
	uint32_t getElapsedFrames();
    
	std::ostream& console() { return std::cout; }
};
