#include "TextureManager.h"
#include "Utils.h"

#include <sstream>

using namespace ci;
using namespace app;
using namespace std;

TextureManager::~TextureManager()
{
    clear();
}

#if defined( CINDER_MSW )
gl::Texture* TextureManager::getTexture(int mswID, const string &mswType, bool useMipmap, bool forceToAlpha, GLenum wrapS, GLenum wrapT)
{
    stringstream oss;
    oss << mswID << mswType << useMipmap << forceToAlpha << wrapS << wrapT;
    
    string key = oss.str();
    uint64_t id = MurmurHash64B((void*)key.data(), key.size(), 0);
    
    if (hasTexture(id))
    {
        return getTexture(id);
    }
    
    DataSourceRef resource = loadResource(mswID, mswType);
    
    gl::Texture *texture = TextureHelper::loadTexture(resource, useMipmap, forceToAlpha, wrapS, wrapT);
    putTexture(id, texture);
    
    return texture;
}
#else
gl::Texture* TextureManager::getTexture(const string &macPath, bool useMipmap, bool forceToAlpha, GLenum wrapS, GLenum wrapT)
{
    stringstream oss;
    oss << macPath << useMipmap << forceToAlpha << wrapS << wrapT;
    
    string key = oss.str();
    uint64_t id = MurmurHash64B((void*)key.data(), key.size(), 0);
    
    if (hasTexture(id))
    {
        return getTexture(id);
    }
    
    DataSourceRef resource = loadResource(macPath);
    
    gl::Texture *texture = TextureHelper::loadTexture(resource, useMipmap, forceToAlpha, wrapS, wrapT);
    putTexture(id, texture);
    
    return texture;
}
#endif

bool TextureManager::removeTexture(gl::Texture *texture)
{
    for (map<uint64_t, gl::Texture*>::iterator it = cache.begin(); it != cache.end(); ++it)
    {
        if (texture == it->second)
        {
            delete it->second;
            cache.erase(it);

            return true;
        }
    }
    
    return false;
}

void TextureManager::clear()
{
    for (map<uint64_t, gl::Texture*>::const_iterator it = cache.begin(); it != cache.end(); ++it)
    {
        delete it->second;
    }
    
    DLOG(cache.size() << " TEXTURES DELETED");
    
    cache.clear();
}
