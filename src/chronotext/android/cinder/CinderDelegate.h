#pragma once

#include <jni.h>
#include <android/asset_manager.h>
#include <android/sensor.h>

#include "chronotext/cinder/CinderSketch.h"

#include "cinder/android/LogStream.h"

class CinderDelegate
{
    std::shared_ptr<ci::android::dostream> mOutputStream;

    int mWidth;
    int mHeight;

    ci::Timer mTimer;
    uint32_t mFrameCount;

	float mAccelFilterFactor;
	ci::Vec3f mLastAccel, mLastRawAccel;

    ASensorManager *mSensorManager;
    const ASensor *mAccelerometerSensor;
    ASensorEventQueue *mSensorEventQueue;

    static int sensorEventCallback(int fd, int events, void *data)
    {
    	CinderDelegate *instance = (CinderDelegate*)data;
    	instance->processSensorEvents();

    	return 1;
    }

    void processSensorEvents();
    void accelerated(const ci::Vec3f &acceleration);

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
