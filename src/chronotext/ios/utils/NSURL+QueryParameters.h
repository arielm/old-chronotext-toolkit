#import <Foundation/Foundation.h>

@interface NSURL (QueryParameters)

+ (id) URLWithString:(NSString *)URLString queryParameters:(NSDictionary*)queryParameters;

@end
