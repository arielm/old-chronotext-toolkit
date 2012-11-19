#pragma once

#include <jni.h>
#include <android/asset_manager.h>

#include "chronotext/cinder/CinderSketch.h"

#include "cinder/android/LogStream.h"

class CinderDelegate
{
    int mWidth;
    int mHeight;

    ci::Timer mTimer;
    uint32_t mFrameCount;

	float mAccelFilterFactor;
	ci::Vec3f mLastAccel, mLastRawAccel;

	std::shared_ptr<ci::android::dostream> mOutputStream;

public:
    JavaVM *mJavaVM;
    jobject mJavaListener;

    CinderSketch *sketch;
    
    CinderDelegate()
    :
    mLastAccel(ci::Vec3f::zero()),
    mLastRawAccel(ci::Vec3f::zero())
    {}

    virtual ~CinderDelegate() {}

    void launch(AAssetManager *assetManager, JavaVM *javaVM, jobject javaListener);

    void init(int width, int height);
    void draw();
    void event(int id);

    void addTouch(float x, float y);
    void updateTouch(float x, float y);
    void removeTouch(float x, float y);
    
    void accelerated(float x, float y, float z);

	void enableAccelerometer( float updateFrequency = 30, float filterFactor = 0.1f);
	void disableAccelerometer();

    double getElapsedSeconds() const;
    uint32_t getElapsedFrames() const;
    
    int getWindowWidth();
    int getWindowHeight();
    ci::Vec2f getWindowSize();
    float getWindowAspectRatio();
    ci::Area getWindowBounds() const;
    
    std::ostream& console();
    
    void sendMessage(int what, const std::string &body);
    virtual void handleMessage(int what, const std::string &body);
};
