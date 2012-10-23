/*
 * SIMPLE CinderSketch
 *
 * BE SURE TO EVENTUALLY RUN IN "RELEASE" MODE!
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

public:
    Sketch(void *context) : CinderSketch(context) {}

    void setup();
    void shutdown();

    void resize(ci::app::ResizeEvent event);
    void draw();
};
