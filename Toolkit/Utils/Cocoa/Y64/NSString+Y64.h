/*
 * BASED ON https://github.com/cinder/Cinder/blob/master/src/cinder/Base64.cpp
 * AND THE libb64 LIBRARY: http://libb64.sourceforge.net
 *
 * 1) MODIFIED TO BE URL-SAFE:
 * SEE THE Y64 VARIANT IN http://en.wikipedia.org/wiki/Base64#Variants_summary_table
 *
 * 2) WITH TWO NEW ADDITIONS:
 * - stringToBase64String
 * - base64StringToString
 */

#import <Foundation/Foundation.h>

@interface NSString (Y64)

- (NSData*) base64StringToData;
- (NSString*) stringToBase64String;
- (NSString*) base64StringToString;

@end
