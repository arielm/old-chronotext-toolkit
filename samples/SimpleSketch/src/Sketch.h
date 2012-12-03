/*
 * SIMPLE CinderSketch: LOADING A TEXTURE AND DRAGGING IT AROUND...
 *
 * IMPORTANT: RETINA DISPLAYS ARE HANDLED DIFFERENTLY, WHETHER YOU'RE USING A "SIMPLE" OR "COMPLEX" SKETCH, E.G.
 * 1) SIMPLE-SKETCH:  AN IPHONE-4 WILL HAVE A SCREEN SIZE OF 640x960 AND A CONTENT-SCALE OF 1
 * 2) COMPLEX-SKETCH: AN IPHONE-4 WILL HAVE A SCREEN SIZE OF 320x480 AND A CONTENT-SCALE OF 2
 */

#pragma once

#include "chronotext/cinder/CinderSketch.h"
#include "chronotext/texture/TextureManager.h"

class Sketch : public CinderSketch
{
    TextureManager textureManager;
    Texture *texture;
    
    ci::Vec2f dragOrigin;
    ci::Vec2f position;

public:
    Sketch(void *context, void *delegate = NULL)
    :
    CinderSketch(context, delegate)
    {}

    void setup(bool renew);
    void resize(ci::app::ResizeEvent event);
    void draw();
    
    void addTouch(int index, float x, float y);
    void updateTouch(int index, float x, float y);
};
