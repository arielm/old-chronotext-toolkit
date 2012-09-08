#include "TextureManager.h"
#include "Utils.h"

#include <sstream>

using namespace std;
using namespace ci;
using namespace app;

TextureManager::~TextureManager()
{
    for (map<uint64_t, gl::Texture*>::const_iterator it = cache.begin(); it != cache.end(); ++it)
    {
        delete it->second;
    }
}

gl::Texture* TextureManager::getTexture(const string &resourceName, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT)
{
    return getTexture(InputSource::getResource(resourceName), useMipmap, filter, wrapS, wrapT);
}

gl::Texture* TextureManager::getTexture(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT)
{
    stringstream oss;
    oss << inputSource->getUniqueName() << useMipmap << filter << wrapS << wrapT;
    
    string key = oss.str();
    uint64_t id = chr::hash(key);
    
    if (hasTexture(id))
    {
        return getTexture(id);
    }
    else
    {
        gl::Texture *texture = TextureHelper::loadTexture(inputSource, useMipmap, filter, wrapS, wrapT);
        putTexture(id, texture);
        
        return texture;
    }
}

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
