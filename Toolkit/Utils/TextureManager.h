#pragma once

#include "Hasher.h"
#include "TextureHelper.h"

#include "cinder/DataSource.h"
#include "cinder/app/AppBasic.h"

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

#if defined( CINDER_MSW )
    ci::gl::Texture* getTexture(int mswID, const std::string &mswType, bool useMipmap = false, bool forceToAlpha = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
#else
    ci::gl::Texture* getTexture(const std::string &macPath, bool useMipmap = false, bool forceToAlpha = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
#endif
    
    bool removeTexture(ci::gl::Texture *texture);
};
