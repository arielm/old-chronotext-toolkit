#pragma once

#include "cinder/app/AppNative.h"

#include "chronotext/cinder/CinderSketchDelegate.h"
#include "chronotext/os/Handler.h"

class CinderSketchSimple : public Handler, public Looper
{
protected:
    ci::app::AppNative *context;
    CinderSketchDelegate *delegate;

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

    CinderSketchSimple(void *context, CinderSketchDelegate *delegate = NULL)
    :
    Handler(this),
    context(static_cast<ci::app::AppNative*>(context)),
    delegate(delegate)
    {}
    
    virtual ~CinderSketchSimple() {};

    virtual void setup(bool renewContext) {}
    virtual void shutdown() {}
    virtual void resize(ci::app::ResizeEvent event) {}

    virtual void update() {}
    virtual void draw() {}
    
    virtual void start(int flags) {}
    virtual void stop(int flags) {}
    virtual void event(int id) {}
    
    virtual void addTouch(int index, float x, float y) {}
    virtual void updateTouch(int index, float x, float y) {}
    virtual void removeTouch(int index, float x, float y) {}

#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    virtual void accelerated(ci::app::AccelEvent event) {}
    
    void enableAccelerometer(float updateFrequency = 30, float filterFactor = 0.1f) { context->enableAccelerometer(updateFrequency, filterFactor); }
	void disableAccelerometer() { context->disableAccelerometer(); }
#endif
    
    double getElapsedSeconds() const { return context->getElapsedSeconds(); }
    uint32_t getElapsedFrames() const { return context->getElapsedFrames(); }

    float getContentScale() const { return 1; }
    std::ostream& console() { return context->console(); }
    
    void sendStringToDelegate(int what, const std::string &body)
    {
        if (delegate)
        {
            delegate->receiveStringFromSketch(what, body);
        }
    }
};
