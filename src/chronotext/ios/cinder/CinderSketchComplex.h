#pragma once

#include "cinder/app/AppCocoaTouch.h"

#include "chronotext/os/Handler.h"

class CinderSketchComplex : public Handler, public Looper
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
    
    enum
    {
    	EVENT_FOREGROUND,
    	EVENT_BACKGROUND,
    	EVENT_KEY_BACK
    };

    CinderSketchComplex(void *context)
    :
    Handler(this),
    context(context)
    {}
    
    virtual ~CinderSketchComplex() {};

	virtual void setup(bool renewContext) {}
	virtual void shutdown() {}
	virtual void resize(ci::app::ResizeEvent event) {}
	virtual void update() {}
	virtual void draw() {}
	
	virtual void start(int flags) {}
	virtual void stop(int flags) {}
    virtual void event(int id) {}
	
	void touchesBegan(ci::app::TouchEvent event);
	void touchesMoved(ci::app::TouchEvent event);
	void touchesEnded(ci::app::TouchEvent event);
	
	virtual void addTouch(int index, float x, float y) {}
	virtual void updateTouch(int index, float x, float y) {}
	virtual void removeTouch(int index, float x, float y) {}

	virtual void accelerated(ci::app::AccelEvent event) {}

	void enableAccelerometer(float updateFrequency = 30, float filterFactor = 0.1f);
	void disableAccelerometer();

    double getElapsedSeconds();
	uint32_t getElapsedFrames();

	int getWindowWidth();
	int getWindowHeight();
    ci::Vec2f getWindowSize();
    float getWindowAspectRatio();
    ci::Area getWindowBounds() const;
    float getContentScale();

	std::ostream& console() { return std::cout; }
};
