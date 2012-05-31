/*
 * BASED ON https://github.com/cinder/Cinder/blob/master/src/cinder/Base64.cpp
 * AND THE libb64 LIBRARY: http://libb64.sourceforge.net
 *
 * MODIFIED TO BE URL-SAFE:
 * SEE THE Y64 VARIANT IN http://en.wikipedia.org/wiki/Base64#Variants_summary_table
 */

#import <Foundation/Foundation.h>

@interface NSData (Y64)

- (NSString*) dataToBase64String;

@end
