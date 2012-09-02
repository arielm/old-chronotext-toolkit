#include "TextureHelper.h"

#include "cinder/ImageIo.h"

using namespace std;
using namespace ci;

gl::Texture* TextureHelper::loadTexture(DataSourceRef dataSource, bool useMipmap, bool forceToAlpha, GLenum wrapS, GLenum wrapT)
{
    gl::Texture::Format format;
    format.setWrap(wrapS, wrapT);
    
    if (useMipmap)
    {
        format.enableMipmapping(true);
        format.setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    }
    
    if (forceToAlpha)
    {
        Surface surface(loadImage(dataSource));
        Channel8u channel = surface.getChannel(0);
        
        GLenum dataFormat = GL_ALPHA;
        format.setInternalFormat(GL_ALPHA);
        
        // if the data is not already contiguous, we'll need to create a block of memory that is
        if ( ( channel.getIncrement() != 1 ) || ( channel.getRowBytes() != channel.getWidth() * sizeof(uint8_t) ) )
        {
            boost::shared_ptr<uint8_t> data( new uint8_t[channel.getWidth() * channel.getHeight()], checked_array_deleter<uint8_t>() );
            uint8_t *dest = data.get();
            const int8_t inc = channel.getIncrement();
            const int32_t width = channel.getWidth();
            for ( int y = 0; y < channel.getHeight(); ++y )
            {
                const uint8_t *src = channel.getData( 0, y );
                for ( int x = 0; x < width; ++x )
                {
                    *dest++ = *src;
                    src += inc;
                }
            }
            
            return new gl::Texture(data.get(), dataFormat, channel.getWidth(), channel.getHeight(), format);
        }
        else
        {
            return new gl::Texture(channel.getData(), dataFormat, channel.getWidth(), channel.getHeight(), format);
        }
    }
    
    return new gl::Texture(loadImage(dataSource), format);
}

void TextureHelper::bindTexture(gl::Texture *texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->getId());
}

void TextureHelper::drawTextureFromCenter(gl::Texture *texture)
{
    float x1 = -texture->getWidth() * 0.5;
    float y1 = -texture->getHeight() * 0.5;
    
    float x2 = x1 + texture->getWidth();
    float y2 = y1 + texture->getHeight();
    
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
