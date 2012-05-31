#import "NSData+Y64.h"

#include "cencode.h"

@implementation NSData (YBase64String)

- (NSString*) dataToBase64String
{
    int inputSize = self.length;

    if (inputSize == 0)
    {
        return @"";
    }
    
    char *buffer = (char*)malloc(inputSize * 4 / 3 + 4);
    
    base64_encodestate state;
    base64_init_encodestate(&state);
    
    int resultSize = base64_encode_block((const char*)self.bytes, inputSize, &buffer[0], &state);
    resultSize += base64_encode_blockend(&buffer[resultSize], &state);
    buffer[resultSize] = 0; // NULL TERMINATE THE STRING
    
    NSString *result = [NSString stringWithUTF8String:buffer];
    free(buffer);
    
    return result;
}

@end
