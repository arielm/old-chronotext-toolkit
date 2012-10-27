#pragma once

#include "chronotext/cinder/CinderSketch.h"
#include "cinder/app/AppNative.h"

class CinderApp : public ci::app::AppNative
{
    int startCount;
    int updateCount;

public:
    CinderSketch *sketch;
    
    CinderApp()
    :
    startCount(0),
    updateCount(0)
    {}

    void setup();
    void shutdown();
    void resize(ci::app::ResizeEvent event);

    void update();
    void draw();
    
    void mouseDown(ci::app::MouseEvent event);    
    void mouseUp(ci::app::MouseEvent event);    
    void mouseDrag(ci::app::MouseEvent event);
    
#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    void accelerated(ci::app::AccelEvent event);
#endif
    
#if defined(CINDER_ANDROID)
    void pause();
    void resume(bool renewContext);
#endif
};
