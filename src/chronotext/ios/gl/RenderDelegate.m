#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import "chronotext/ios/gl/RenderDelegate.h"
#import "chronotext/ios/gl/EAGLView.h"

@implementation RenderDelegate

@synthesize view;
@synthesize viewController;
@synthesize dt;

- (void) startWithReason:(int)reason
{}

- (void) stopWithReason:(int)reason
{}

- (void) setup
{}

- (void) draw
{}

// ======================================== TOUCH ========================================

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{}

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{}

@end
