#import "AppDelegate.h"
#import "EAGLViewController.h"

#include "Sketch.h"

int main(int argc, char *argv[])
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppDelegate");
    [pool release];
    return retVal;
}

@implementation AppDelegate

- (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    viewController = [[EAGLViewController alloc] initWithProperties:
                      [NSDictionary dictionaryWithObjectsAndKeys:
                       [NSNumber numberWithBool:NO], kES1RendererPropertyUseDepthBuffer,
                       [NSNumber numberWithInt:1], kEAGLViewPropertyAnimationFrameInterval,
                       [NSNumber numberWithBool:YES], kEAGLViewPropertyMultipleTouchEnabled,
                       nil]];
    
    viewController.renderDelegate = self;

    sketch = new Sketch(self);

    window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
    window.backgroundColor = [UIColor blackColor];
    
    [window setRootViewController:viewController];
    [window makeKeyAndVisible];
    
    return YES;
}

- (void) dealloc
{
    sketch->shutdown();
    delete sketch;
    
    [viewController release];
    [window release];

    [super dealloc];
}

@end
