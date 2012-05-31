#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

OBJC_EXPORT NSString* kES1RendererPropertyUseDepthBuffer;

@interface ES1Renderer : NSObject
{
	NSDictionary *properties;
	EAGLContext *context;
	
	// The pixel dimensions of the CAEAGLLayer
	GLint backingWidth;
	GLint backingHeight;
	
	GLuint defaultFramebuffer, colorRenderbuffer;
	GLuint depthRenderbuffer;
}

@property (nonatomic, readonly) NSDictionary *properties;

- (id) initWithProperties:(NSDictionary *)properties;
- (void) beginRendering;
- (void) endRendering;
- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;

@end
