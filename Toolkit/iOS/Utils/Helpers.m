#import "Helpers.h"

@implementation Helpers

+ (NSString*) pathForFileInDocuments:(NSString*)name
{
	NSString *documentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	return [documentsPath stringByAppendingPathComponent:name];
}

+ (NSString*) pathForFileInBundle:(NSString*)name
{
	return [[NSBundle mainBundle] pathForResource:name ofType:nil];
}

+ (BOOL) isStringValid:(NSString*)string
{
    return (string && (string.length > 0));
}

+ (BOOL) isStringEmpty:(NSString*)string
{
	NSString *trimmed = [string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
	return ([trimmed length] > 0);
}

+ (NSString*) safeString:(NSString*)string
{
    if (string && (string.length > 0))
    {
        return [string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
    }
    
    return @"";
}

+ (NSString*) md5ForData:(NSData*)data
{
    unsigned char result[CC_MD5_DIGEST_LENGTH];
    CC_MD5(data.bytes, data.length, result);
    
    return [NSString stringWithFormat:
            @"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
            result[0], result[1], result[2], result[3], result[4], result[5], result[6], result[7],
            result[8], result[9], result[10], result[11], result[12], result[13], result[14], result[15]
            ];
}

+ (UINavigationController*) presentModalNavigationControllerWithRootViewController:(UIViewController*)rootViewController fromViewController:(UIViewController*)viewController
{
    UINavigationController *navController = [[[UINavigationController alloc] initWithRootViewController:rootViewController] autorelease];
    navController.modalPresentationStyle = UIModalPresentationFormSheet;
    
    if (UI_USER_INTERFACE_IDIOM() != UIUserInterfaceIdiomPad)
    {
        navController.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    }

    [viewController presentModalViewController:navController animated:YES];
    
    return navController;
}

@end
