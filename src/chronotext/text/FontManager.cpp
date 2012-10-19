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

XFont* FontManager::getFont(const string &resourceName, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot)
{
    return getFont(InputSource::getResource(resourceName), useMipmap, useAnisotropy, maxDimensions, charactersPerSlot);
}

XFont* FontManager::getFont(InputSourceRef inputSource, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot)
{
    stringstream oss;
    oss << inputSource->getUniqueName() << useMipmap << useAnisotropy << maxDimensions << charactersPerSlot;
    
    string key = oss.str();
    uint64_t id = chr::hash(key);
    
    if (hasFont(id))
    {
        return getFont(id);
    }
    
    XFont *font = new XFont(inputSource, useMipmap, useAnisotropy, maxDimensions, charactersPerSlot);
    putFont(id, font);
    
    return font;
}

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
