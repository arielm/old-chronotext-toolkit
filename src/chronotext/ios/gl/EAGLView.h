#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#import "chronotext/ios/gl/ES1Renderer.h"

OBJC_EXPORT NSString* kEAGLViewPropertyAnimationFrameInterval;
OBJC_EXPORT NSString* kEAGLViewPropertyMultipleTouchEnabled;

@class EAGLViewController;

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView
{
	
	ES1Renderer *renderer;
	
	BOOL animating;
	NSInteger animationFrameInterval;
	CADisplayLink *displayLink;
	
	EAGLViewController *viewController;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic, assign) NSInteger animationFrameInterval;
@property (nonatomic, assign) EAGLViewController *viewController;

- (id) initWithFrame:(CGRect)frame properties:(NSDictionary *)properties;
- (void) startAnimation;
- (void) stopAnimation;
- (void) drawView:(id)sender;

@end
