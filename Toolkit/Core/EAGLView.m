#import "EAGLView.h"
#import "EAGLViewController.h"

NSString* kEAGLViewPropertyAnimationFrameInterval = @"kEAGLViewPropertyAnimationFrameInterval";
NSString* kEAGLViewPropertyMultipleTouchEnabled = @"kEAGLViewPropertyMultipleTouchEnabled";

@implementation EAGLView

@synthesize animating;
@synthesize animationFrameInterval;
@synthesize viewController;

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithFrame:(CGRect)frame properties:(NSDictionary *)properties;
{    
    if ((self = [super initWithFrame:frame]))
	{
        self.contentScaleFactor = [UIScreen mainScreen].scale;

        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking,
										kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat,
										nil];
		
		renderer = [[ES1Renderer alloc] initWithProperties:properties];
		if (!renderer)
		{
			[self release];
			return nil;
		}

		animating = FALSE;

		animationFrameInterval = [[properties objectForKey:kEAGLViewPropertyAnimationFrameInterval] intValue];
		self.multipleTouchEnabled = [[properties objectForKey:kEAGLViewPropertyMultipleTouchEnabled] boolValue];
    }
	
    return self;
}

- (void) drawView:(id)sender
{
    [renderer beginRendering];
	[viewController draw];
	[renderer endRendering];
}

- (void) layoutSubviews
{
	[renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self drawView:nil];
}

- (void) setAnimationFrameInterval:(NSInteger)frameInterval
{
	// Frame interval defines how many display frames must pass between each time the
	// display link fires. The display link will only fire 30 times a second when the
	// frame internal is two on a display that refreshes 60 times a second. The default
	// frame interval setting of one will fire 60 times a second when the display refreshes
	// at 60 times a second. A frame interval setting of less than one results in undefined
	// behavior.
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;
		
		if (animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void) startAnimation
{
	if (!animating)
	{
		displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
		[displayLink setFrameInterval:animationFrameInterval];
		[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		
		animating = TRUE;
	}
}

- (void) stopAnimation
{
	if (animating)
	{
		[displayLink invalidate];
		displayLink = nil;
		
		animating = FALSE;
	}
}

- (void) dealloc
{
    [renderer release];
    [super dealloc];
}

// ======================================== TOUCH ========================================

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	[viewController.renderDelegate touchesBegan:touches withEvent:event];
	[super touchesBegan:touches withEvent:event];
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	[viewController.renderDelegate touchesMoved:touches withEvent:event];
	[super touchesMoved:touches withEvent:event];
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	[viewController.renderDelegate touchesEnded:touches withEvent:event];
	[super touchesEnded:touches withEvent:event];
}

- (void) touchesCancelled:(NSSet*)touches withEvent:(UIEvent*)event
{
	[viewController.renderDelegate touchesCancelled:touches withEvent:event];
	[super touchesCancelled:touches withEvent:event];
}

@end
