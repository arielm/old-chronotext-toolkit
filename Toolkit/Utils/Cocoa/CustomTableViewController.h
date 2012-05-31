#import <UIKit/UIKit.h>

@interface CustomTableViewController : UIViewController <UITableViewDelegate, UITableViewDataSource>
{
    UITableViewStyle tableViewStyle;
}

@property (nonatomic, retain) UITableView *tableView;
@property (nonatomic, retain) UIToolbar *toolbar;

- (id) initWithStyle:(UITableViewStyle)style;
- (void) setToolbarHidden:(BOOL)hidden;

@end
