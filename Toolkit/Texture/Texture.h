#pragma once

#include "TextureHelper.h"

class Texture
{
    GLuint name;
    int width;
    int height;
    
    InputSourceRef inputSource;
    bool useMipmap;
    int filter;
    GLenum wrapS;
    GLenum wrapT;
    
    ci::gl::Texture *texture;
    
    void init(ci::gl::Texture *texture);

public:
    Texture(InputSourceRef inputSource, bool useMipmap = false, int filter = TextureHelper::FILTER_NONE, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE);
    ~Texture();
    
    void unload();
    void reload();
    
    void bind();
    
    void begin();
    void end();
    
    void drawFromCenter();
    void draw(float rx = 0, float ry = 0);
};
