#import "EAGLViewController.h"
#import "RenderDelegate.h"

NSString* kEAGLViewControllerPropertyInterfaceOrientation = @"kEAGLViewControllerPropertyInterfaceOrientation";

@interface EAGLViewController ()

- (void) startWithReason:(int)reason;
- (void) stopWithReason:(int)reason;

@end

@implementation EAGLViewController

@synthesize properties;
@synthesize interfaceOrientation;
@synthesize renderDelegate;

- (id) initWithProperties:(NSDictionary *)_properties;
{
	if (self = [super init])
	{
		properties = [_properties retain];
        
        id object = [properties objectForKey:kEAGLViewControllerPropertyInterfaceOrientation];
        if (object != nil)
        {
            interfaceOrientation = [object intValue];
        }
        else
        {
            interfaceOrientation = UIInterfaceOrientationPortrait;
        }
	}

	return self;
}

- (void) dealloc
{
	[properties release];
    [glView release];
	[renderDelegate release];
	
	[super dealloc];
}

- (void) loadView
{
	glView = [[EAGLView alloc] initWithFrame:UIScreen.mainScreen.bounds properties:properties];
	glView.viewController = self;
	self.view = glView;

	// ---

	renderDelegate.view = glView;
	renderDelegate.viewController = self;
	
	/* 
	 * MUST TAKE PLACE *AFTER* EAGLView CREATION
	 * (A VALID GL CONTEXT IS REQUIRED...)
	 */
	[renderDelegate setup];
}

- (void) viewWillAppear:(BOOL)animated
{
    NSLog(@"EAGLViewController - viewWillAppear");
	[self startWithReason:REASON_VIEW_WILL_APPEAR];
	
	NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	[center addObserver:self selector:@selector(applicationDidBecomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];
	[center addObserver:self selector:@selector(applicationWillResignActive) name:UIApplicationWillResignActiveNotification object:nil];
}

- (void) viewWillDisappear:(BOOL)animated
{
    NSLog(@"EAGLViewController - viewWillDisappear");
	[self stopWithReason:REASON_VIEW_WILL_DISAPEAR];
	
	NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
	[center removeObserver:self name:UIApplicationDidBecomeActiveNotification object:nil];
	[center removeObserver:self name:UIApplicationWillResignActiveNotification object:nil];
}

- (void) draw
{
	now = [NSDate timeIntervalSinceReferenceDate];

    if (ticks == 0)
    {
		t0 = now;
		renderDelegate.dt = 1.0 / 60 * glView.animationFrameInterval;
    }
    else
    {
		renderDelegate.dt = (now - then);
    }
	
    ticks++;
    elapsed = now - t0;
    then = now;

    [renderDelegate draw];
}

- (void) startWithReason:(int)reason
{
    if (!started)
    {
        ticks = 0;
        
        [glView startAnimation];
        [renderDelegate startWithReason:reason];
        
        started = YES;
    }
}

- (void) stopWithReason:(int)reason
{
    if (started)
    {
        NSLog(@"AVERAGE FRAME-RATE: %f FRAMES PER SECOND", [self averageFPS]);
        
        [glView stopAnimation];
        [renderDelegate stopWithReason:reason];
        
        started = NO;
    }
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
	return (toInterfaceOrientation == interfaceOrientation);
}

- (double) averageFPS
{
    return ticks / elapsed;
}

// ============================================ NOTIFICATIONS ============================================

- (void) applicationDidBecomeActive
{
	NSLog(@"EAGLViewController - applicationDidBecomeActive");
	[self startWithReason:REASON_APPLICATION_DID_BECOME_ACTIVE];
}

- (void) applicationWillResignActive
{
	NSLog(@"EAGLViewController - applicationWillResignActive");
    [self stopWithReason:REASON_APPLICATION_WILL_RESIGN_ACTIVE];
}

@end
