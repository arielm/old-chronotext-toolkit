/*
 * ...
 */

#pragma once

#include "CinderSketch.h"
#include "TextureManager.h"
#include "Texture.h"

class Sketch : public CinderSketch
{
    TextureManager textureManager;
    
    ci::gl::Texture *texture1;
    ci::gl::Texture *texture2;
    ci::gl::Texture *texture3;

public:
    Sketch(void *context) : CinderSketch(context) {}

    void setup();
    void shutdown();
    void resize(ci::app::ResizeEvent event);

    void draw();
};
