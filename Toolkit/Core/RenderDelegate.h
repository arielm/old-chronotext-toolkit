@class EAGLView;
@class EAGLViewController;

enum
{
    REASON_VIEW_WILL_APPEAR,
    REASON_VIEW_WILL_DISAPEAR,
    REASON_APPLICATION_DID_BECOME_ACTIVE,
    REASON_APPLICATION_WILL_RESIGN_ACTIVE
};

@interface RenderDelegate : NSObject
{
	EAGLView *view;
	EAGLViewController *viewController;
	float dt;
}

@property (nonatomic, assign) EAGLView *view;
@property (nonatomic, assign) EAGLViewController *viewController;
@property (nonatomic, assign) float dt;

- (void) startWithReason:(int)reason;
- (void) stopWithReason:(int)reason;

- (void) setup;
- (void) draw;

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end
