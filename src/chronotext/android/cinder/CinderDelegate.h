#pragma once

#include "chronotext/cinder/CinderSketch.h"

#include "cinder/android/LogStream.h"

class CinderDelegate
{
    int mWidth;
	int mHeight;

	ci::Timer mTimer;
	uint32_t mFrameCount;

    std::shared_ptr<ci::android::dostream> mOutputStream;

public:
	CinderSketch *sketch;

	void event(int id);
	void init(int width, int height);
	void draw();

	void addTouch(float x, float y);
	void updateTouch(float x, float y);
	void removeTouch(float x, float y);
    
    double getElapsedSeconds() const;
	uint32_t getElapsedFrames() const;
    
    int getWindowWidth();
	int getWindowHeight();
    ci::Vec2f getWindowSize();
    float getWindowAspectRatio();
    ci::Area getWindowBounds() const;
    
    std::ostream& console();
};
