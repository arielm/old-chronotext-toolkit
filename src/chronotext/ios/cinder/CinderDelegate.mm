#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import "CinderDelegate.h"
#import "EAGLViewController.h"

using namespace ci;
using namespace app;
using namespace std;

@implementation CinderDelegate

@synthesize sketch;
@synthesize accelFilterFactor = mAccelFilterFactor;
@synthesize width = mWidth;
@synthesize height = mHeight;
@synthesize contentScale = mContentScale;

- (id) init
{
	if (self = [super init])
	{
		mLastAccel = mLastRawAccel = Vec3f::zero();
	}
	
	return self;
}

- (void) dealloc
{
	[super dealloc];
}

- (void) startWithReason:(int)reason
{
	mFrameCount = 0;
	mTimer.start();
	sketch->start(reason == REASON_VIEW_WILL_APPEAR ? CinderSketch::FLAG_FOCUS_GAIN : CinderSketch::FLAG_APP_RESUME);
}

- (void) stopWithReason:(int)reason
{
	mTimer.stop();
	sketch->stop(reason == REASON_VIEW_WILL_DISAPEAR ? CinderSketch::FLAG_FOCUS_LOST : CinderSketch::FLAG_APP_PAUSE);
}

- (void) setup
{
    int mx;
    int my;
    
    switch (viewController.interfaceOrientation)
    {
        case UIInterfaceOrientationLandscapeLeft:
        case UIInterfaceOrientationLandscapeRight:
            mx = 0;
            my = 1;
            break;
            
        case UIInterfaceOrientationPortrait:
        case UIInterfaceOrientationPortraitUpsideDown:
            mx = 1;
            my = 0;
            break;
    }
    
    int frameWidth = view.frame.size.width;
    int frameHeight = view.frame.size.height;
    
	mWidth = mx * frameWidth + my * frameHeight;
	mHeight = mx * frameHeight + my * frameWidth;
    
    mContentScale = view.contentScaleFactor;

	sketch->setup(false);
	sketch->resize(ResizeEvent(Vec2i(mWidth, mHeight)));
}

- (void) draw
{
	sketch->update();
	sketch->draw();
	mFrameCount++;
}

- (double) elapsedSeconds
{
    return mTimer.getSeconds();
}

- (uint32_t) elapsedFrames
{
    return mFrameCount;
}

// ======================================== ACCELEROMETER ========================================

- (void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
	Vec3f direction(acceleration.x, acceleration.y, acceleration.z);
	Vec3f filtered = mLastAccel * (1 - mAccelFilterFactor) + direction * mAccelFilterFactor;

	AccelEvent event(filtered, direction, mLastAccel, mLastRawAccel);
	sketch->accelerated(event);
	
	mLastAccel = filtered;
	mLastRawAccel = direction;
}

// ======================================== TOUCH ========================================

- (uint32_t) addTouchToMap:(UITouch*)touch
{
	uint32_t candidateId = 0;
	bool found = true;
	while (found)
	{
		candidateId++;
		found = false;
		for (map<UITouch*,uint32_t>::const_iterator mapIt = mTouchIdMap.begin(); mapIt != mTouchIdMap.end(); ++mapIt)
		{
			if (mapIt->second == candidateId)
			{
				found = true;
				break;
			}
		}
	}
	
	mTouchIdMap.insert(make_pair(touch, candidateId));
	return candidateId;
}

- (void) removeTouchFromMap:(UITouch*)touch
{
	map<UITouch*,uint32_t>::iterator found(mTouchIdMap.find(touch));
	if (found == mTouchIdMap.end())
	{
		cout << "Couldn' find touch in map?" << endl;
	}
	else
	{
		mTouchIdMap.erase(found);
	}
}

- (uint32_t) findTouchInMap:(UITouch*)touch
{
	map<UITouch*,uint32_t>::const_iterator found(mTouchIdMap.find(touch));
	if (found == mTouchIdMap.end())
	{
		cout << "Couldn' find touch in map?" << endl;
		return 0;
	}
	else
	{
		return found->second;
	}
}

- (void) updateActiveTouches
{
	static float contentScale = 1;
	
	vector<TouchEvent::Touch> activeTouches;
	for (map<UITouch*,uint32_t>::const_iterator touchIt = mTouchIdMap.begin(); touchIt != mTouchIdMap.end(); ++touchIt)
	{
		CGPoint pt = [touchIt->first locationInView:view];
		CGPoint prevPt = [touchIt->first previousLocationInView:view];
		activeTouches.push_back(TouchEvent::Touch(Vec2f(pt.x, pt.y) * contentScale, Vec2f(prevPt.x, prevPt.y) * contentScale, touchIt->second, [touchIt->first timestamp], touchIt->first));
	}
}

// ---

- (void) touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
	static float contentScale = 1;
	
	vector<TouchEvent::Touch> touchList;
	for (UITouch *touch in touches)
	{
		CGPoint pt = [touch locationInView:view];
		CGPoint prevPt = [touch previousLocationInView:view];
		touchList.push_back(TouchEvent::Touch(Vec2f(pt.x, pt.y) * contentScale, Vec2f(prevPt.x, prevPt.y) * contentScale, [self addTouchToMap:touch], [touch timestamp], touch));
	}
	
	[self updateActiveTouches];
	if (!touchList.empty())
	{
		sketch->touchesBegan(TouchEvent(touchList));
	}
}

- (void) touchesMoved:(NSSet*)touches withEvent:(UIEvent*)event
{
	static float contentScale = 1;
	
	vector<TouchEvent::Touch> touchList;
	for (UITouch *touch in touches)
	{
		CGPoint pt = [touch locationInView:view];
		CGPoint prevPt = [touch previousLocationInView:view];			
		touchList.push_back(TouchEvent::Touch(Vec2f(pt.x, pt.y) * contentScale, Vec2f(prevPt.x, prevPt.y) * contentScale, [self findTouchInMap:touch], [touch timestamp], touch));
	}
	
	[self updateActiveTouches];
	if (!touchList.empty())
	{
		sketch->touchesMoved(TouchEvent(touchList));
	}
}

- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
	static float contentScale = 1;
	
	vector<TouchEvent::Touch> touchList;
	for (UITouch *touch in touches)
	{
		CGPoint pt = [touch locationInView:view];
		CGPoint prevPt = [touch previousLocationInView:view];
		touchList.push_back(TouchEvent::Touch(Vec2f(pt.x, pt.y) * contentScale, Vec2f(prevPt.x, prevPt.y) * contentScale, [self findTouchInMap:touch], [touch timestamp], touch));
		[self removeTouchFromMap:touch];
	}
	
	[self updateActiveTouches];
	if (!touchList.empty())
	{
		sketch->touchesEnded(TouchEvent(touchList));
	}
}

- (void) touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
	[self touchesEnded:touches withEvent:event];
}

@end
