#include "PVRHelper.h"

#include <zlib.h>
#include <stdexcept>

using namespace std;
using namespace ci;

#define PVR_TEXTURE_FLAG_TYPE_MASK 0xff

/*
 * PVR VERSION 2
 * ASSERTION: BYTE-ORDER IS OK FOR INTEL AND ARM
 */
struct PVRTexHeader
{
    uint32_t headerLength;
    uint32_t height;
    uint32_t width;
    uint32_t numMipmaps;
    uint32_t flags;
    uint32_t dataLength;
    uint32_t bpp;
    uint32_t bitmaskRed;
    uint32_t bitmaskGreen;
    uint32_t bitmaskBlue;
    uint32_t bitmaskAlpha;
    uint32_t pvrTag;
    uint32_t numSurfs;
};

enum
{
    kPVRTexturePixelTypeRGBA_4444 = 0x10,
    kPVRTexturePixelTypeRGBA_5551,
    kPVRTexturePixelTypeRGBA_8888,
    kPVRTexturePixelTypeRGB_565,
    kPVRTexturePixelTypeRGB_555,
    kPVRTexturePixelTypeRGB_888,
    kPVRTexturePixelTypeI_8,
    kPVRTexturePixelTypeAI_88,
    kPVRTexturePixelTypePVRTC_2,
    kPVRTexturePixelTypePVRTC_4,	
    kPVRTexturePixelTypeBGRA_8888,
    kPVRTexturePixelTypeA_8
};

static bool isPOT(int n)
{
    return (n && !(n & (n - 1)));
}

/*
 * BASED ON http://www.codeandweb.com/blog/2011/05/03/loading-gzip-compressed-pvr-textures-without-realloc
 */
Buffer PVRHelper::loadCompressedPVR(const fs::path &filePath)
{
    gzFile file = gzopen(filePath.c_str(), "rb");
    if (!file)
    {
        throw runtime_error("PVR.GZ: CAN'T OPEN FILE");
    }
    
    PVRTexHeader header;
    if (gzread(file, &header, sizeof(header)) != sizeof(header))
    {
        gzclose(file);
        throw runtime_error("PVR.GZ: HEADER ERROR");
    }
    
    if (header.pvrTag != 559044176)
    {
        gzclose(file);
        throw runtime_error("PVR.GZ: FORMAT ERROR");
    }
    
    Buffer buffer(sizeof(header) + header.dataLength);
    
    char *data = (char*)buffer.getData();
    if (!data)
    {
        gzclose(file);
        throw runtime_error("PVR.GZ: OUT-OF-MEMORY");
    }
    
    memcpy(data, &header, sizeof(header));
    
    if (gzread(file, data + sizeof(header), header.dataLength) != header.dataLength)
    {
        gzclose(file);
        throw runtime_error("PVR.GZ: DECOMPRESSION ERROR");
    }
    
    gzclose(file);
    return buffer;
}

gl::Texture* PVRHelper::getPVRTexture(const Buffer &buffer, bool useMipmap, GLenum wrapS, GLenum wrapT)
{
    PVRTexHeader *header = (PVRTexHeader*)buffer.getData();
    
    GLsizei width = header->width;
    GLsizei height = header->height;
    
    if (!isPOT(width) || !isPOT(height))
    {
        throw runtime_error("PVR TEXTURE: DIMENSIONS MUST BE A POWER-OF-TWO");
    }

    GLenum internalFormat;
    GLenum format;
    GLenum type;
    
    switch (header->flags & PVR_TEXTURE_FLAG_TYPE_MASK)
    {
        case kPVRTexturePixelTypeRGBA_4444:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_SHORT_4_4_4_4;
            break;
            
        case kPVRTexturePixelTypeRGBA_8888:
            internalFormat = GL_RGBA;
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
            
        case kPVRTexturePixelTypeRGB_565:
            internalFormat = GL_RGB;
            format = GL_RGB;
            type = GL_UNSIGNED_SHORT_5_6_5;
            break;
            
        case kPVRTexturePixelTypeRGB_888:
            internalFormat = GL_RGB;
            format = GL_RGB;
            type = GL_UNSIGNED_BYTE;
            break;
            
        case kPVRTexturePixelTypeA_8:
            internalFormat = GL_ALPHA;
            format = GL_ALPHA;
            type = GL_UNSIGNED_BYTE;
            break;
            
        default:
            throw runtime_error("PVR TEXTURE: UNSUPPORTED PIXEL-TYPE");
    }
    
    char *data = (char*)buffer.getData() + header->headerLength;
    
    GLuint name;
    glGenTextures(1, &name);
    
    glBindTexture(GL_TEXTURE_2D, name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    
    if (useMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
    
    if (useMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
    }
    
    return new gl::Texture(GL_TEXTURE_2D, name, width, height, false);
}
