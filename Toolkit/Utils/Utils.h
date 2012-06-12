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
