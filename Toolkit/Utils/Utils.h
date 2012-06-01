#pragma once

#include "cinder/app/App.h"
#include "cinder/Utilities.h"

#include <string>
#include <fstream>
#include <iostream>

#if defined( CINDER_COCOA )
#include "cinder/cocoa/CinderCocoa.h"
#define SAFE_AUTORELEASE ci::cocoa::SafeNsAutoreleasePool autorelease
#else
#define SAFE_AUTORELEASE
#endif

// ---

#if defined(DEBUG) || defined(FORCE_LOG) || defined(LOG_TO_FILE)
#define DLOG(x) std::cout << x << std::endl
#else
#define DLOG(x)
#endif

// ---

/*
 * cout REDIRECTION
 * AS DESCRIBED IN http://www.cplusplus.com/reference/iostream/ios/rdbuf/
 */

static std::streambuf *backup;
static std::ofstream filestr;

static void logToFile(std::string filePath)
{
    filestr.open(filePath.c_str());
    backup = std::cout.rdbuf();
    
    std::streambuf *psbuf = filestr.rdbuf();
    std::cout.rdbuf(psbuf);
}

/*
 * ASSERTION: logToFile() WAS PREVIOUSLY CALLED
 */
static void logToConsole()
{
    std::cout.rdbuf(backup);
    filestr.close();
}

// ---

/*
 * THE WINDOWS CODE IS FROM cinder/Utilities.h
 * THE OSX/IOS CODE HAD TO BE ADAPTED
 */

std::string wstringToUtf8(const std::wstring &s);
std::wstring utf8ToWstring(const std::string &s);

// ---

ci::fs::path getCachesDirectory();

// ---

static std::string loadText(ci::DataSourceRef dataSource)
{
    if (dataSource->isFilePath())
	{
        std::ifstream file (dataSource->getFilePath().c_str(), std::ios::in|std::ios::binary|std::ios::ate);
        
        size_t size = file.tellg();
        char *data = new char[size];
        
        file.seekg(0, std::ios::beg);
        file.read(data, size);
        file.close();
        
        std::string s;
        s.assign(data, size);
        delete[] data;
        
        return s;
    }
    else
    {
        return std::string((char*)dataSource->getBuffer().getData(), dataSource->getBuffer().getDataSize());
    }
}

// ---

/*
 * THE FOLLOWING SWAPPING FUNCTIONS ARE DUPLICATES FROM cinder/Utilities.h
 * THEY WERE UNUSABLE IN THAT CONTEXT BECAUSE OF THE extern DECLARATION
 */

static inline int16_t _swapEndian( int16_t val ) { 
	return (int16_t) (	(((uint16_t) (val) & (uint16_t) 0x00ffU) << 8) | 
					  (((uint16_t) (val) & (uint16_t) 0xff00U) >> 8) );
}

static inline uint16_t _swapEndian( uint16_t val ) { 
	return (uint16_t) (	(((uint16_t) (val) & (uint16_t) 0x00ffU) << 8) | 
					   (((uint16_t) (val) & (uint16_t) 0xff00U) >> 8) );
}

static inline int32_t _swapEndian( int32_t val ) { 
	return (int32_t)((((uint32_t) (val) & (uint32_t) 0x000000FFU) << 24) |
					 (((uint32_t) (val) & (uint32_t) 0x0000FF00U) <<  8) |
					 (((uint32_t) (val) & (uint32_t) 0x00FF0000U) >>  8) |
					 (((uint32_t) (val) & (uint32_t) 0xFF000000U) >> 24));
}

static inline uint32_t _swapEndian( uint32_t val ) { 
	return (uint32_t)((((uint32_t) (val) & (uint32_t) 0x000000FFU) << 24) |
					  (((uint32_t) (val) & (uint32_t) 0x0000FF00U) <<  8) |
					  (((uint32_t) (val) & (uint32_t) 0x00FF0000U) >>  8) |
					  (((uint32_t) (val) & (uint32_t) 0xFF000000U) >> 24));
}

static inline float _swapEndian( float val ) { 
	uint32_t temp = _swapEndian( * reinterpret_cast<uint32_t*>( &val ) );
	return *(reinterpret_cast<float*>( &temp ) );
}

static inline double _swapEndian( double val ) {
	union {
		double d;
		struct {  
			uint32_t a;
			uint32_t b;
		} i;
	} s1, s2;
	s1.d = val;
	s2.i.a = _swapEndian( s1.i.b );
	s2.i.b = _swapEndian( s1.i.a	);
	return s2.d;
}
