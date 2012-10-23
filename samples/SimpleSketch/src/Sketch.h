/*
 * BASIC CinderSketch
 *
 * BE SURE TO EVENTUALLY RUN IN "RELEASE" MODE!
 */

#pragma once

#include "chronotext/cinder/CinderSketch.h"
#include "chronotext/texture/TextureHelper.h"

class Sketch : public CinderSketch
{
	ci::gl::Texture *texture;

public:
    Sketch(void *context) : CinderSketch(context) {}

    void setup();
    void shutdown();
    void resize(ci::app::ResizeEvent event);

    void start(int flags);
    void stop(int flags);

    void update();
    void draw();

#if defined(CINDER_COCOA_TOUCH) || defined(CINDER_ANDROID)
    void accelerated(ci::app::AccelEvent event);
#endif
};
