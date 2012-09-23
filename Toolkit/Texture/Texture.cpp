#include "Texture.h"
#include "Utils.h"

using namespace std;
using namespace ci;

Texture::Texture(InputSourceRef inputSource, bool useMipmap, int filter, GLenum wrapS, GLenum wrapT)
:
inputSource(inputSource),
useMipmap(useMipmap),
filter(filter),
wrapS(wrapS),
wrapT(wrapT)
{
    init(TextureHelper::loadTexture(inputSource, useMipmap, filter, wrapS, wrapT));
}

Texture::~Texture()
{
    unload();
}

/*
 * ASSERTION: texture IS NULL
 */
void Texture::init(ci::gl::Texture *texture)
{
    this->texture = texture;

    name = texture->getId();
    width = texture->getWidth();
    height = texture->getHeight();
}

void Texture::unload()
{
    if (texture)
    {
        TextureHelper::deleteTexture(texture);
        texture = NULL;
    }
}

void Texture::reload()
{
    if (!texture)
    {
        init(TextureHelper::loadTexture(inputSource, useMipmap, filter, wrapS, wrapT));
    }
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, name);
}

void Texture::begin()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, name);
}

void Texture::end()
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Texture::drawFromCenter()
{
    draw(width * 0.5, height * 0.5);
}

void Texture::draw(float rx, float ry)
{
    float x1 = -rx;
    float y1 = -ry;
    
    float x2 = x1 + width;
    float y2 = y1 + height;
    
    const GLfloat vertices[] =
    {
        x1, y1,
        x2, y1,
        x2, y2,
        x1, y2
    };
    
    const GLfloat coords[] =
    {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };
    
    glTexCoordPointer(2, GL_FLOAT, 0, coords);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
