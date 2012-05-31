#pragma once

#include "Hasher.h"
#include "XFont.h"

#include "cinder/DataSource.h"
#include "cinder/app/AppBasic.h"

#include <map>

/*
 * TODO:
 *
 * A BETTER VERSION SHOULD RETURN A "DERIVED" FONT WHENEVER POSSIBLE
 *
 * E.G. WHEN ASKING FOR A FONT-ALREADY DEFINED, BUT WITH DIFFERENT PARAMETERS (useAnisotropy, maxDimensions OR charactersPerSlot)
 */

class FontManager
{
    std::map<uint64_t, XFont*> cache;
    
    bool hasFont(uint64_t id)
    {
        return (cache.count(id) > 0);
    }
    
    XFont* getFont(uint64_t id)
    {
        return cache[id];
    }
    
    void putFont(uint64_t id, XFont *font)
    {
        cache[id] = font;
    }

public:
    ~FontManager();
    
#if defined( CINDER_COCOA )
    XFont* getFont(const std::string &macPath, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
#else
    XFont* getFont(int mswID, const std::string &mswType, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
#endif
    
    bool removeFont(XFont *font);
};
