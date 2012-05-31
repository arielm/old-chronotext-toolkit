#import "NSString+URLEncode.h"

@implementation NSString (URLEncode)

- (NSString*) urlEncoded
{
    NSString *result = (NSString*) CFURLCreateStringByAddingPercentEscapes(NULL,
                                                                           (CFStringRef)self,
                                                                           NULL,
                                                                           CFSTR(" !\"#$%&'()*+'-./:;<=>?@[\\]^_`{|}~"),
                                                                           kCFStringEncodingUTF8);
    return [result autorelease];
}

@end
