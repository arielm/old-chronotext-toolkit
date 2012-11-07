/*
 * SIMPLE CinderSketch: LOADING A TEXTURE AND DRAG IT AROUND...
 *
 * WARNING: THE "SIMPLE-SKETCH" SYSTEM IS NOT ADAPTED FOR IOS RETINA
 * THE "COMPLEX-SKETCH" SYSTEM ON THE OTHER-HAND BEHAVES EQUALLY ON RETINA AND REGULAR DEVICES
 */

#pragma once

#include "chronotext/cinder/CinderSketch.h"
#include "chronotext/texture/TextureHelper.h"

class Sketch : public CinderSketch
{
    ci::gl::Texture *texture;
    
    ci::Vec2f dragOrigin;
    ci::Vec2f position;

public:
    Sketch(void *context) : CinderSketch(context) {}

    void setup(bool renew);
    void shutdown();

    void resize(ci::app::ResizeEvent event);
    void draw();
    
    void addTouch(int index, float x, float y);
    void updateTouch(int index, float x, float y);
};
