/*
 * BASIC CinderSketch
 *
 * BE SURE TO EVENTUALLY RUN IN "RELEASE" MODE!
 */

#pragma once

#include "CinderSketch.h"

class Sketch : public CinderSketch
{
public:
    Sketch(void *context) : CinderSketch(context) {}

	void setup();
	void shutdown();
	void resize(ci::app::ResizeEvent event);
	
	void start(int flags);
	void stop(int flags);
	
	void update();
	void draw();

#if defined( CINDER_COCOA_TOUCH )
    void accelerated(ci::app::AccelEvent event);
#endif
};
