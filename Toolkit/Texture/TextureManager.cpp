#include "TextureManager.h"

using namespace std;
using namespace ci;
using namespace app;

TextureManager::~TextureManager()
{
    for (list<TextureEntry>::const_iterator it = cache.begin(); it != cache.end(); ++it)
    {
        TextureHelper::deleteTexture(it->texture);
    }
}

gl::Texture* TextureManager::getTextureFromCache(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT)
{
    for (list<TextureEntry>::const_iterator it = cache.begin(); it != cache.end(); ++it)
    {
        if ((it->inputSource == inputSource) && (it->useMipmap == useMipmap) && (it->filter == filter) && (it->wrapS == wrapS) && (it->wrapT == wrapT))
        {
            return it->texture;
        }
    }
    
    return NULL;
}

void TextureManager::putTextureInCache(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT, gl::Texture *texture)
{
    cache.push_back(TextureEntry(inputSource, useMipmap, filter, wrapS, wrapT, texture));
}

gl::Texture* TextureManager::getTexture(const string &resourceName, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT)
{
    return getTexture(InputSource::getResource(resourceName), useMipmap, filter, wrapS, wrapT);
}

gl::Texture* TextureManager::getTexture(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT)
{
    gl::Texture *texture = getTextureFromCache(inputSource, useMipmap, filter, wrapS, wrapT);
    
    if (!texture)
    {
        texture = TextureHelper::loadTexture(inputSource, useMipmap, filter, wrapS, wrapT);
        putTextureInCache(inputSource, useMipmap, filter, wrapS, wrapT, texture);
    }
    
    return texture;
}

bool TextureManager::removeTexture(gl::Texture *texture)
{
    for (list<TextureEntry>::iterator it = cache.begin(); it != cache.end(); ++it)
    {
        if (texture == it->texture)
        {
            TextureHelper::deleteTexture(it->texture);
            cache.erase(it);

            return true;
        }
    }
    
    return false;
}

void TextureManager::clear()
{
    for (list<TextureEntry>::const_iterator it = cache.begin(); it != cache.end(); ++it)
    {
        TextureHelper::deleteTexture(it->texture);
    }

    cache.clear();
}

void TextureManager::reload()
{
    for (list<TextureEntry>::const_iterator it = cache.begin(); it != cache.end(); ++it)
    {
        TextureHelper::deleteTexture(it->texture);
    }
    
    for (list<TextureEntry>::iterator it = cache.begin(); it != cache.end(); ++it)
    {
        it->texture = TextureHelper::loadTexture(it->inputSource, it->useMipmap, it->filter, it->wrapS, it->wrapT);
    }
}
