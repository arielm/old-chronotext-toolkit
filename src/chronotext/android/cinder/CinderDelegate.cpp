#include "chronotext/android/cinder/CinderDelegate.h"
#include "chronotext/InputSource.h"

using namespace ci;
using namespace ci::app;
using namespace std;

enum
{
	EVENT_ATTACHED = 1,
	EVENT_DETACHED,
	EVENT_PAUSED,
	EVENT_RESUMED,
    EVENT_SHOWN,
    EVENT_HIDDEN,
	EVENT_DESTROYED
};

void CinderDelegate::launch(AAssetManager *assetManager, JavaVM *javaVM, jobject javaListener)
{
	InputSource::setAndroidAssetManager(assetManager);
    
	mJavaVM = javaVM;
	mJavaListener = javaListener;
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

void CinderDelegate::event(int id)
{
	switch (id)
	{
		case EVENT_ATTACHED:
        case EVENT_SHOWN:
			mFrameCount = 0;
			mTimer.start();
			sketch->start(CinderSketch::FLAG_FOCUS_GAIN);
			break;
            
		case EVENT_RESUMED:
			mFrameCount = 0;
			mTimer.start();
            
            /*
             * ASSERTION: THE GL CONTEXT HAS JUST BEEN RE-CREATED
             */
        	sketch->setup(true);
        	sketch->resize(ResizeEvent(Vec2i(mWidth, mHeight)));
            
			sketch->start(CinderSketch::FLAG_APP_RESUME);
			break;
            
		case EVENT_DETACHED:
        case EVENT_HIDDEN:
			mTimer.stop();
			sketch->stop(CinderSketch::FLAG_FOCUS_LOST);
			break;
            
		case EVENT_PAUSED:
			mTimer.stop();
			sketch->stop(CinderSketch::FLAG_APP_PAUSE);
			break;

		case EVENT_DESTROYED:
			sketch->shutdown();
			delete sketch;
			break;
	}
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

ostream& CinderDelegate::console()
{
    if (!mOutputStream)
    {
        mOutputStream = shared_ptr<cinder::android::dostream>(new android::dostream);
    }
    
    return *mOutputStream;
}

void CinderDelegate::sendMessage2(int what, const string &body)
{
	JNIEnv *env;
	mJavaVM->GetEnv((void**)&env, JNI_VERSION_1_4);
   
	jclass cls = env->GetObjectClass(mJavaListener);
	jmethodID method = env->GetMethodID(cls, "handleMessage", "(ILjava/lang/String;)V");
	env->CallVoidMethod(mJavaListener, method, what, env->NewStringUTF(body.c_str()));
}

void CinderDelegate::handleMessage(int what, const string &body)
{}
