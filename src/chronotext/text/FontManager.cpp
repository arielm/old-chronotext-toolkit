#include "chronotext/text/FontManager.h"
#include "chronotext/utils/Utils.h"

#include <sstream>

using namespace ci;
using namespace app;
using namespace std;

FontManager::~FontManager()
{
    for (map<uint64_t, XFont*>::const_iterator it = cache.begin(); it != cache.end(); ++it)
    {
        delete it->second;
    }
    
    DLOG(cache.size() << " FONTS DELETED");
}

#if defined( CINDER_COCOA )
XFont* FontManager::getFont(const string &macPath, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot)
{
    stringstream oss;
    oss << macPath << useMipmap << useAnisotropy << maxDimensions << charactersPerSlot;
    
    string key = oss.str();
    uint64_t id = chr::hash(key);
    
    if (hasFont(id))
    {
        return getFont(id);
    }
    
    DataSourceRef resource = loadResource(macPath);

    XFont *font = new XFont(resource, useMipmap, useAnisotropy, maxDimensions, charactersPerSlot);
    putFont(id, font);
    
    return font;
}
#else
XFont* FontManager::getFont(int mswID, const string &mswType, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot)
{
    stringstream oss;
    oss << mswID << mswType << useMipmap << useAnisotropy << maxDimensions << charactersPerSlot;
    
    string key = oss.str();
    uint64_t id = chr::hash(key);
    
    if (hasFont(id))
    {
        return getFont(id);
    }
    
    DataSourceRef resource = loadResource(mswID, mswType);

    XFont *font = new XFont(resource, useMipmap, useAnisotropy, maxDimensions, charactersPerSlot);
    putFont(id, font);
    
    return font;
}
#endif

bool FontManager::removeFont(XFont *font)
{
    for (map<uint64_t, XFont*>::iterator it = cache.begin(); it != cache.end(); ++it)
    {
        if (font == it->second)
        {
            delete it->second;
            cache.erase(it);
            
            return true;
        }
    }
    
    return false;
}