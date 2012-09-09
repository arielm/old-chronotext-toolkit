#import <UIKit/UIKit.h>

#import "EAGLView.h"
#import "RenderDelegate.h"

OBJC_EXPORT NSString* kEAGLViewControllerPropertyInterfaceOrientation;

@interface EAGLViewController : UIViewController
{
	NSDictionary *properties;
    int interfaceOrientation;
    EAGLView *glView;
	RenderDelegate *renderDelegate;
	
	BOOL started;
    BOOL stopped;

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
