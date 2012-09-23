/*
 * ...
 */

#pragma once

#include "CinderSketch.h"
#include "TextureManager.h"

class Sketch : public CinderSketch
{
    TextureManager textureManager;
    
    Texture *texture1;
    Texture *texture2;
    Texture *texture3;

public:
    Sketch(void *context) : CinderSketch(context) {}

    void setup();
    void shutdown();
    void resize(ci::app::ResizeEvent event);

    void draw();
};
