#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CommonCrypto/CommonDigest.h>

@interface Helpers : NSObject

+ (NSString*) pathForFileInDocuments:(NSString*)name;
+ (NSString*) pathForFileInBundle:(NSString*)name;

+ (BOOL) isStringValid:(NSString*)string;
+ (BOOL) isStringEmpty:(NSString*)string;

+ (NSString*) md5ForData:(NSData*)data;

+ (UINavigationController*) presentModalNavigationControllerWithRootViewController:(UIViewController*)rootViewController fromViewController:(UIViewController*)wiewController;

@end
