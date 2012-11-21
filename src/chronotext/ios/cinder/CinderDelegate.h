#import "RenderDelegate.h"

#include "chronotext/cinder/CinderSketch.h"

#include <map>

@interface CinderDelegate : RenderDelegate <UIAccelerometerDelegate>
{
	CinderSketch *sketch;
	
	std::map<UITouch*,uint32_t>	mTouchIdMap;

	float mAccelFilterFactor;
	ci::Vec3f mLastAccel, mLastRawAccel;
    
    int mWidth;
    int mHeight;
    float mContentScale;
    
	ci::Timer mTimer;
	uint32_t mFrameCount;
    
    BOOL mInitialized;
    BOOL mActive;
}

@property (nonatomic, assign) CinderSketch *sketch;
@property (nonatomic, assign) float accelFilterFactor;
@property (nonatomic, readonly) int width;
@property (nonatomic, readonly) int height;
@property (nonatomic, readonly) float contentScale;
@property (nonatomic, readonly) double elapsedSeconds;
@property (nonatomic, readonly) uint32_t elapsedFrames;
@property (nonatomic, readonly) BOOL initialized;
@property (nonatomic, readonly) BOOL active;

- (uint32_t) addTouchToMap:(UITouch*)touch;
- (void) removeTouchFromMap:(UITouch*)touch;
- (uint32_t) findTouchInMap:(UITouch*)touch;
- (void) updateActiveTouches;

@end
