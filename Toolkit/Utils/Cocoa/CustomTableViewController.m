#import "CustomTableViewController.h"

@implementation CustomTableViewController

@synthesize tableView = _tableView;
@synthesize toolbar = _toolbar;

- (id) init
{
	if (self = [super init])
	{
        tableViewStyle = UITableViewStylePlain;
    }
    
	return self;
}

- (id) initWithStyle:(UITableViewStyle)style
{
	if (self = [super init])
	{
		tableViewStyle = style;
	}
    
	return self;
}

- (void) dealloc
{
    [_tableView release];
    [_toolbar release];

    [super dealloc];
}

- (void) loadView
{
	[super loadView];
	
	self.tableView = [[[UITableView alloc] initWithFrame:self.view.bounds style:tableViewStyle] autorelease];
	_tableView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
	_tableView.delegate = self;
	_tableView.dataSource = self;
	[self.view addSubview:_tableView];
}

- (void) viewWillAppear:(BOOL)animated
{
	[_tableView deselectRowAtIndexPath:[_tableView indexPathForSelectedRow] animated:animated];
}  

- (void) viewDidAppear:(BOOL)animated
{
	[_tableView flashScrollIndicators];
}

- (void) setEditing:(BOOL)editing animated:(BOOL)animated
{
	[super setEditing:editing animated:animated];
	[_tableView setEditing:editing animated:animated];
}

// ======================================== TOOLBAR ========================================

- (void) setToolbarHidden:(BOOL)hidden
{
    CGFloat viewHeight = CGRectGetHeight(self.view.bounds);
    CGFloat viewWidth = CGRectGetWidth(self.view.bounds);

    if (hidden)
    {
        if (self.toolbar)
        {
            [_toolbar removeFromSuperview];
            self.toolbar = nil;
            
            CGRect tableFrame = CGRectMake(0, 0, viewWidth, viewHeight);
            [self.tableView setFrame:tableFrame];
        }
    }
    else if (!self.toolbar)
    {
        self.toolbar = [[UIToolbar new] autorelease];
        _toolbar.barStyle = UIBarStyleDefault;
        _toolbar.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleTopMargin;
        
        [_toolbar sizeToFit];
        CGFloat toolbarHeight = CGRectGetHeight(_toolbar.frame);
        
        CGRect toolbarFrame = CGRectMake(0, viewHeight - toolbarHeight, viewWidth, toolbarHeight);
        [_toolbar setFrame:toolbarFrame];
        
        [self.view addSubview:_toolbar];
        
        CGRect tableFrame = CGRectMake(0, 0, viewWidth, viewHeight - toolbarHeight);
        [self.tableView setFrame:tableFrame];
    }
}

// ======================================== UITableViewDataSource ========================================

- (NSInteger) tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 0;
}

- (UITableViewCell *) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	return nil;
}

@end
