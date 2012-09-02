#pragma once

#include "cinder/gl/Texture.h"

typedef boost::shared_ptr<class ci::gl::Texture> TextureRef;

class TextureHelper
{
public:
    static ci::gl::Texture* loadTexture(const std::string &resourceName, bool useMipmap = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    static ci::gl::Texture* loadTexture(ci::DataSourceRef dataSource, bool useMipmap = false, bool forceToAlpha = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);

    static void bindTexture(ci::gl::Texture *texture);
    static void drawTextureFromCenter(ci::gl::Texture *texture);
};
