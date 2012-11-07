#pragma once

#include "chronotext/utils/Hasher.h"
#include "chronotext/font/XFont.h"

#include <map>

/*
 * TODO:
 * 1) UNLOAD / RELOAD MECHANISM, SIMILAR TO THE ONE IN TextureManager
 * 2) THE CACHE COULD BE SIMILAR TO THE ONE IN TextureManager
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
    
    XFont* getFont(const std::string &resourceName, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
    XFont* getFont(InputSourceRef inputSource, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
    
    bool removeFont(XFont *font);
};
