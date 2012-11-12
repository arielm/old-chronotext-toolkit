#include "chronotext/android/cinder/CinderDelegate.h"

using namespace ci;
using namespace ci::app;
using namespace std;

enum
{
	EVENT_ATTACHED = 1,
	EVENT_DETACHED,
	EVENT_PAUSE,
	EVENT_RESUME,
	EVENT_DESTROYED
};

void CinderDelegate::event(int id)
{
	switch (id)
	{
		case EVENT_ATTACHED:
			mFrameCount = 0;
			mTimer.start();
			sketch->start(CinderSketch::FLAG_FOCUS_GAIN);
			break;

		case EVENT_RESUME:
			mFrameCount = 0;
			mTimer.start();
			sketch->start(CinderSketch::FLAG_APP_RESUME);
			break;

		case EVENT_DETACHED:
			mTimer.stop();
			sketch->stop(CinderSketch::FLAG_FOCUS_LOST);
			break;

		case EVENT_PAUSE:
			mTimer.stop();
			sketch->stop(CinderSketch::FLAG_APP_PAUSE);
			break;

		case EVENT_DESTROYED:
			sketch->shutdown();
			delete sketch;
			break;
	}
}

void CinderDelegate::init(int width, int height)
{
	mWidth = width;
	mHeight = height;

	sketch->setup(false);
	sketch->resize(ResizeEvent(Vec2i(mWidth, mHeight)));
}

void CinderDelegate::draw()
{
    sketch->update();
    sketch->draw();
    mFrameCount++;
}

void CinderDelegate::addTouch(float x, float y)
{
	sketch->addTouch(0, x, y);
}

void CinderDelegate::updateTouch(float x, float y)
{
	sketch->updateTouch(0, x, y);
}

void CinderDelegate::removeTouch(float x, float y)
{
	sketch->removeTouch(0, x, y);
}

double CinderDelegate::getElapsedSeconds() const
{
    return mTimer.getSeconds();
}

uint32_t CinderDelegate::getElapsedFrames() const
{
    return mFrameCount;
}

int CinderDelegate::getWindowWidth()
{
    return mWidth;
}

int CinderDelegate::getWindowHeight()
{
    return mHeight;
}

Vec2f CinderDelegate::getWindowSize()
{
    return Vec2f(mWidth, mHeight);
}

float CinderDelegate::getWindowAspectRatio()
{
    return mWidth / (float)mHeight;
}

Area CinderDelegate::getWindowBounds() const
{
    return Area(0, 0, mWidth, mHeight);
}
