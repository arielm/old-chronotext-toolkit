#import "NSURL+QueryParameters.h"
#import "NSString+URLEncode.h"

@implementation NSURL (QueryParameters)

+ (id) URLWithString:(NSString *)URLString queryParameters:(NSDictionary*)queryParameters
{
    NSMutableString *output = [NSMutableString stringWithString:URLString];
    int n = 0;
    
    for (id key in queryParameters)
    {
        NSString *keyString = (NSString*)key;
        id value = [queryParameters objectForKey:key];
        
        if (![value isKindOfClass:[NSNull class]])
        {
            NSString *valueString = [value description];
            
            if (valueString.length > 0)
            {
                if (n++ == 0)
                {
                    [output appendString:@"?"];
                }
                else
                {
                    [output appendString:@"&"];
                }
                
                [output appendString:[NSString stringWithFormat:@"%@=%@", keyString, [valueString urlEncoded]]];
            }
        }
    }
    
    return [NSURL URLWithString:output];
}

@end
