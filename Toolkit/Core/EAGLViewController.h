#import <UIKit/UIKit.h>

#import "EAGLView.h"

OBJC_EXPORT NSString* kEAGLViewControllerPropertyInterfaceOrientation;

@class RenderDelegate;

@interface EAGLViewController : UIViewController
{
	NSDictionary *properties;
    int interfaceOrientation;
    EAGLView *glView;
	RenderDelegate *renderDelegate;
	
	BOOL started;

	int ticks;
	NSTimeInterval t0;
	NSTimeInterval now, then;
	NSTimeInterval elapsed;
}

@property (nonatomic, readonly) NSDictionary *properties;
@property (nonatomic, readonly) int interfaceOrientation;
@property (nonatomic, retain) RenderDelegate *renderDelegate;
@property (nonatomic, readonly) double averageFPS;

- (id) initWithProperties:(NSDictionary *)properties;
- (void) draw;

@end
