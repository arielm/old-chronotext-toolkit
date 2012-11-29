#pragma once

#include "cinder/app/App.h"
#include "cinder/Utilities.h"

#include <string>
#include <fstream>
#include <iostream>

#if defined(DEBUG) || defined(FORCE_LOG) || defined(LOG_TO_FILE)
#define DLOG(x) std::cout << x << std::endl
#else
#define DLOG(x)
#endif

// ---

/*
 * cout REDIRECTION, FOR COCOA ONLY
 * AS DESCRIBED IN http://www.cplusplus.com/reference/iostream/ios/rdbuf/
 */

static std::streambuf *gCoutBackup = NULL;
static std::ofstream gCoutFilestr;

static void logToFile(const ci::fs::path &filePath)
{
    if (!gCoutBackup)
    {
        gCoutFilestr.open(filePath.c_str());
        gCoutBackup = std::cout.rdbuf();
        
        std::streambuf *psbuf = gCoutFilestr.rdbuf();
        std::cout.rdbuf(psbuf);
    }
}

static void logToConsole()
{
    if (gCoutBackup)
    {
        std::cout.rdbuf(gCoutBackup);
        gCoutFilestr.close();
        gCoutBackup = NULL;
    }
}

// ---

/*
 * THE WINDOWS CODE IS FROM cinder/Utilities.h
 * THE OSX/IOS CODE HAD TO BE ADAPTED
 */

std::string wstringToUtf8(const std::wstring &s);
std::wstring utf8ToWstring(const std::string &s);
