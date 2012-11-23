#pragma once

#include "cinder/app/AppNative.h"
#include "chronotext/cinder/CinderSketch.h"

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
    
    void touchesBegan(ci::app::TouchEvent event);
	void touchesMoved(ci::app::TouchEvent event);
	void touchesEnded(ci::app::TouchEvent event);
    
#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    void accelerated(ci::app::AccelEvent event);
#endif
    
#if defined(CINDER_ANDROID)
    void pause();
    void resume(bool renewContext);
#endif
    
    void receiveStringFromSketch(int what, const std::string &body);
    void sendStringToSketch(int what, const std::string &body);
};
