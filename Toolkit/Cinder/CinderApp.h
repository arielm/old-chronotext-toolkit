#pragma once

#include "CinderSketch.h"

class CinderApp : public ci::app::AppBasic
{
public:
	void setup();
    void shutdown();
	void resize(ci::app::ResizeEvent event);

	void update();
	void draw();
	
	void mouseDown(ci::app::MouseEvent event);	
	void mouseUp(ci::app::MouseEvent event);	
	void mouseDrag(ci::app::MouseEvent event);
	
	CinderSketch *sketch;
};
