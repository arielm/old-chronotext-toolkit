#if defined( CINDER_COCOA ) && ( ! defined( __OBJC__ ) )
#error "This file must be compiled as Objective-C++ on the Mac"
#endif

#include "Utils.h"

using namespace std;
using namespace ci;

string wstringToUtf8(const wstring &s)
{
#if defined( CINDER_MSW )
	int utf8Size = ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, NULL, 0, NULL, NULL );
	if( utf8Size == 0 )
	{
		throw exception( "Error in UTF-16 to UTF-8 conversion." );
	}
	
	vector<char> resultString( utf8Size );
	
	int convResult = ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, &resultString[0], utf8Size, NULL, NULL );
	
	if( convResult != utf8Size )
	{
		throw exception( "Error in UTF-16 to UTF-8 conversion." );
	}
	
	return string( &resultString[0] );
#else
    /*
     * AUTORELEASED VERSION
     */
	// int length = s.size() * sizeof(wchar_t);
	// NSString *utf32NS = [[[NSString alloc] initWithBytes:s.data() length:length encoding:NSUTF32LittleEndianStringEncoding] autorelease];
	// return string([utf32NS UTF8String]);

	int length = s.size() * sizeof(wchar_t);
    NSString *utf32NS = [[NSString alloc] initWithBytes:s.data() length:length encoding:NSUTF32LittleEndianStringEncoding];
    
    length = [utf32NS lengthOfBytesUsingEncoding:NSUTF8StringEncoding] + 1;
    char buffer[length];
    memset (buffer, 0, length);

    [utf32NS getCString:buffer maxLength:length encoding:NSUTF8StringEncoding];
    [utf32NS release];
    
    return string(buffer);
#endif
}

wstring utf8ToWstring(const string &s)
{
#if defined( CINDER_MSW )
	int wideSize = ::MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, NULL, 0 );
	if( wideSize == ERROR_NO_UNICODE_TRANSLATION )
	{
		throw exception( "Invalid UTF-8 sequence." );
	}
	else if( wideSize == 0 )
	{
		throw exception( "Error in UTF-8 to UTF-16 conversion." );
	}
	
	vector<wchar_t> resultString( wideSize );
	int convResult = ::MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, &resultString[0], wideSize );
	if( convResult != wideSize )
	{
		throw exception( "Error in UTF-8 to UTF-16 conversion." );
	}
	
	return wstring( &resultString[0] );
#else
    /*
     * AUTORELEASED VERSION
     */
	// NSString *utf8NS = [NSString stringWithCString:s.c_str() encoding:NSUTF8StringEncoding];
	// return wstring(reinterpret_cast<const wchar_t*>([utf8NS cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]));
    
    NSString *utf8NS = [[NSString alloc] initWithUTF8String:s.c_str()];
    
    int length = [utf8NS lengthOfBytesUsingEncoding:NSUTF32LittleEndianStringEncoding] + sizeof(wchar_t);
    char buffer[length];
    memset (buffer, 0, length);

    [utf8NS getCString:buffer maxLength:length encoding:NSUTF32LittleEndianStringEncoding];
    [utf8NS release];
    
    return wstring(reinterpret_cast<const wchar_t*>(buffer));
#endif
}

fs::path getCachesDirectory()
{
#if defined( CINDER_COCOA_TOUCH )
	NSString *cachesPath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
	return string([cachesPath cStringUsingEncoding:NSUTF8StringEncoding]) + "/";
#else
	return ci::getTemporaryDirectory();
#endif
}
