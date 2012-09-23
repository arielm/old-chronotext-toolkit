#pragma once

#include "TextureHelper.h"
#include "InputSource.h"
#include "Utils.h"

#include <list>

struct TextureEntry
{
    InputSourceRef inputSource;
    bool useMipmap;
    int filter;
    GLenum wrapS;
    GLenum wrapT;
    
    ci::gl::Texture *texture;
    
    TextureEntry(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT, ci::gl::Texture *texture)
    :
    inputSource(inputSource),
    useMipmap(useMipmap),
    filter(filter),
    wrapS(wrapS),
    wrapT(wrapT),
    texture(texture)
    {}
};

class TextureManager
{
    std::list<TextureEntry> cache;
    
    ci::gl::Texture* getTextureFromCache(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT);
    void putTextureInCache(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT, ci::gl::Texture *texture);
    
public:
    ~TextureManager();

    ci::gl::Texture* getTexture(const std::string &resourceName, bool useMipmap = false, int filter = TextureHelper::FILTER_NONE, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    ci::gl::Texture* getTexture(InputSourceRef inputSource, bool useMipmap = false, int filter = TextureHelper::FILTER_NONE, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    
    bool removeTexture(ci::gl::Texture *texture);
    void clear();
    void reload();
};
