#pragma once

#include "chronotext/cinder/CinderSketch.h"

class CinderDelegate
{
	// ci::Timer mTimer;
	// uint32_t mFrameCount;

public:
    int mWidth;
	int mHeight;

	CinderSketch *sketch;

	void event(int id);
	void init(int width, int height);
	void draw();

	void addTouch(float x, float y);
	void updateTouch(float x, float y);
	void removeTouch(float x, float y);
};
