#pragma once

#include "chronotext/font/XFont.h"

class FontManager
{
    std::list<XFont*> cache;
    
    XFont* getFromCache(InputSourceRef inputSource, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
    void putInCache(XFont *font);

public:
    ~FontManager();
    
    XFont* getFont(const std::string &resourceName, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
    XFont* getFont(InputSourceRef inputSource, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
    
    bool remove(XFont *font);
    void clear();
    
    void unload();
    void reload();
};
