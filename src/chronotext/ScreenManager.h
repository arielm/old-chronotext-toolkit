#pragma once

#include "chronotext/cinder/CinderSketch.h"

#include <list>
#include <map>

class ScreenManager : public CinderSketch
{
    std::list<CinderSketch*> screens;
    
    ci::Vec2i size;
    
    std::map<CinderSketch*, int> focused;

public:
    CinderSketch *currentScreen;

    ScreenManager(void *context, void *delegate)
    :
    CinderSketch(context, delegate),
    currentScreen(NULL)
    {}

    void shutdown();
    void resize(ci::app::ResizeEvent event);
    
    void update();
    void draw();
    
    void start(int flags);
    void stop(int flags);
    void event(int id);
    
    void addTouch(int index, float x, float y);
    void updateTouch(int index, float x, float y);
    void removeTouch(int index, float x, float y);

#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    void accelerated(ci::app::AccelEvent event);
#endif

    void handleMessage(const Message &message);

    void addScreen(CinderSketch *screen);
    void removeScreen(CinderSketch *screen);
    
    void setCurrentScreen(CinderSketch *screen);
};
