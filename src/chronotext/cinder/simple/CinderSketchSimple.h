#pragma once

#include "cinder/app/AppNative.h"

class CinderSketchSimple
{
protected:
    ci::app::AppNative *context;

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

    CinderSketchSimple(void *context)
    {
        this->context = (ci::app::AppNative*)context;
    }

    virtual void setup() {}
    virtual void shutdown() {}
    virtual void resize(ci::app::ResizeEvent event) {}

    virtual void update() {}
    virtual void draw() {}
    
    virtual void start(int flags) {}
    virtual void stop(int flags) {}
    
    virtual void addTouch(int index, float x, float y) {}
    virtual void updateTouch(int index, float x, float y) {}
    virtual void removeTouch(int index, float x, float y) {}
    
    float getContentScale() const { return 1; }
    
    double getElapsedSeconds() const { return context->getElapsedSeconds(); }
    uint32_t getElapsedFrames() const { return context->getElapsedFrames(); }
    std::ostream& console() { return context->console(); }
    
#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    virtual void accelerated(ci::app::AccelEvent event) {}
    
    void enableAccelerometer(float updateFrequency = 30.0f, float filterFactor = 0.1f) { context->enableAccelerometer(updateFrequency, filterFactor); }
	void disableAccelerometer() {context->disableAccelerometer(); }
#endif
};
