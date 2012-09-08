#pragma once

#include "Hasher.h"
#include "TextureHelper.h"
#include "InputSource.h"

#include <map>

class TextureManager
{
    std::map<uint64_t, ci::gl::Texture*> cache;
    
    bool hasTexture(uint64_t id)
    {
        return (cache.count(id) > 0);
    }

    ci::gl::Texture* getTexture(uint64_t id)
    {
        return cache[id];
    }
    
    void putTexture(uint64_t id, ci::gl::Texture *texture)
    {
        cache[id] = texture;
    }
    
public:
    ~TextureManager();

    ci::gl::Texture* getTexture(const std::string &resourceName, bool useMipmap = false, int filter = TextureHelper::FILTER_NONE, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    ci::gl::Texture* getTexture(InputSourceRef inputSource, bool useMipmap = false, int filter = TextureHelper::FILTER_NONE, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    
    bool removeTexture(ci::gl::Texture *texture);
    void clear();
};
