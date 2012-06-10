#pragma once

#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

typedef boost::shared_ptr<class ci::gl::Texture> TextureRef;

class TextureHelper
{
public:
    static ci::gl::Texture* loadTexture(ci::DataSourceRef dataSource, bool useMipmap = false, bool forceToAlpha = false, GLenum wrapS = GL_CLAMP_TO_EDGE, GLenum wrapT = GL_CLAMP_TO_EDGE)
    {
        ci::gl::Texture::Format format;
        format.setWrap(wrapS, wrapT);
        
        if (useMipmap)
        {
            format.enableMipmapping(true);
            format.setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
        }
        
        if (forceToAlpha)
        {
            ci::Surface surface(loadImage(dataSource));
            ci::Channel8u channel = surface.getChannel(0);
            
            GLint dataFormat = GL_ALPHA;
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
                
                return new ci::gl::Texture(data.get(), dataFormat, channel.getWidth(), channel.getHeight(), format);
            }
            else
            {
                return new ci::gl::Texture(channel.getData(), dataFormat, channel.getWidth(), channel.getHeight(), format);
            }
        }
        
        return new ci::gl::Texture(loadImage(dataSource), format);
    }

    static void bindTexture(ci::gl::Texture *texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture->getId());
    }

    static void drawTextureFromCenter(ci::gl::Texture *texture, bool originUp = true, float cx = 0.5f, float cy = 0.5f)
    {
        float x1 = -texture->getWidth() * cx;
        float y1 = -texture->getHeight() * cy;
        
        float x2 = x1 + texture->getWidth();
        float y2 = y1 + texture->getHeight();
        
        const GLfloat vertices[] =
        {
            x1, y1,
            x2, y1,
            x2, y2,
            x1, y2
        };
        
        float ty1 = originUp ? 0 : 1;
        float ty2 = originUp ? 1 : 0;
        
        const GLfloat coords[] =
        {
            0, ty1,
            1, ty1,
            1, ty2,
            0, ty2
        };
        
        glTexCoordPointer(2, GL_FLOAT, 0, coords);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
};
