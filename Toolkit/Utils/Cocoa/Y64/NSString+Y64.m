#import "NSString+Y64.h"
#import "NSData+Y64.h"

#include "cdecode.h"

@implementation NSString (Y64)

- (NSData*) base64StringToData
{
    NSData *input = [self dataUsingEncoding:NSUTF8StringEncoding];
    int inputSize = input.length;
    
    int outputSize = inputSize / 4 * 3;
    NSMutableData *result = [NSMutableData dataWithLength:outputSize];
    
    if (inputSize >= 4)
    {
        base64_decodestate state;
        base64_init_decodestate(&state);
        
        int actualSize = base64_decode_block((const char*)input.bytes, inputSize, (char*)result.bytes, &state);
        [result setLength:actualSize];
    }
    
    return result;
}

- (NSString*) stringToBase64String
{
    NSData *data = [self dataUsingEncoding:NSUTF8StringEncoding];
    return [data dataToBase64String];
}

- (NSString*) base64StringToString
{
    NSData *data = [self base64StringToData];
    return [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
}

@end
