#import <Foundation/Foundation.h>

@interface NSMutableDictionary (Merge)

+ (id) dictionaryWithObjectsFromDictionary:(NSDictionary*)otherDictionary withKeys:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;
- (void) addObjectsFromDictionary:(NSDictionary*)otherDictionary withKeys:(id)firstKey, ... NS_REQUIRES_NIL_TERMINATION;

@end
