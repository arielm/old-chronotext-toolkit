#include "chronotext/font/XFont.h"
#include "chronotext/utils/DataStreamIO.h"

using namespace std;
using namespace cinder;

inline bool isSpace(wchar_t c)
{
    return ((c == 0x20) || (c == 0xa0));
}

XFont::XFont(DataSourceRef dataSource, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot) : useMipmap(useMipmap), useAnisotropy(useAnisotropy), maxDimensions(maxDimensions), charactersPerSlot(charactersPerSlot)
{
    derived = false;
    read(dataSource);
}

XFont::XFont(XFont *source, bool useAnisotropy, int maxDimensions, int charactersPerSlot) : useAnisotropy(useAnisotropy), maxDimensions(maxDimensions), charactersPerSlot(charactersPerSlot)
{
    numChars = source->numChars;
    w = source->w;
    h = source->h;
    le = source->le;
    te = source->te;
    lw = source->lw;
    
    nativeFontSize = source->nativeFontSize;
    spaceWidth = source->spaceWidth;
    height = source->height;
    maxAscent = source->maxAscent;
    maxDescent = source->maxDescent;
    strikethroughOffset = source->strikethroughOffset;
    
    lookup8bits = source->lookup8bits;
    lookup16bits = source->lookup16bits;
    ordered16bits = source->ordered16bits;
    
    lookup8Len = source->lookup8Len;
    lookup16Len = source->lookup16Len;
    
    tx1 = source->tx1;
    ty1 = source->ty1;
    tx2 = source->tx2;
    ty2 = source->ty2;
    
    anisotropyAvailable = source->anisotropyAvailable;
    maxAnisotropy = source->maxAnisotropy;
    
    name = source->name;

    derived = true;
    init();
}

XFont::~XFont()
{
    if (!derived)
    {
        delete[] w;
        delete[] h;
        delete[] le;
        delete[] te;
        delete[] lw;
        
        delete[] lookup8bits;
        delete[] lookup16bits;
        delete[] ordered16bits;
        
        delete[] tx1;
        delete[] ty1;
        delete[] tx2;
        delete[] ty2;
        
        glDeleteTextures(1, &name);
    }

    // ---
    
    delete[] vertice;
    delete[] coords;
    delete[] indices;
}

void XFont::read(DataSourceRef dataSource)
{
    if (dataSource->isFilePath())
    {
        ifstream in(dataSource->getFilePath().c_str(), ifstream::binary);
        readFromStream(in);
        in.close();
    }
    else
    {
        ReadStreamBuffer tmp(dataSource->getBuffer());
        istream in(&tmp);
        readFromStream(in);
    }
}

void XFont::readFromStream(istream &in)
{
    numChars = DataStreamIO::readBig<uint16_t>(in);
    nativeFontSize = DataStreamIO::readBig<uint16_t>(in);
    spaceWidth = DataStreamIO::readBig<float>(in);
    height = DataStreamIO::readBig<float>(in);
    maxAscent = DataStreamIO::readBig<float>(in);
    maxDescent = DataStreamIO::readBig<float>(in);
    strikethroughOffset = DataStreamIO::readBig<float>(in);
    
    w = new float[numChars];
    h = new float[numChars];
    le = new float[numChars];
    te = new float[numChars];
    lw = new float[numChars];
    
    for (int i = 0; i < numChars; i++)
    {
        w[i] = DataStreamIO::readBig<uint16_t>(in);
        h[i] = DataStreamIO::readBig<uint16_t>(in);
        le[i] = DataStreamIO::readBig<int16_t>(in);
        te[i] = DataStreamIO::readBig<int16_t>(in);
        lw[i] = DataStreamIO::readBig<float>(in);
    }
    
    // ---
    
    lookup8Len = 256 - '!';
    lookup8bits = new int[lookup8Len];
    
    for (int i = 0; i < lookup8Len; i++)
    {
        lookup8bits[i] = DataStreamIO::readBig<uint16_t>(in);
    }
    
    lookup16Len = DataStreamIO::readBig<uint16_t>(in);
    lookup16bits = new int[lookup16Len];
    ordered16bits = new int[lookup16Len];
    
    for (int i = 0; i < lookup16Len; i++)
    {
        lookup16bits[i] = DataStreamIO::readBig<uint16_t>(in);
        ordered16bits[i] = DataStreamIO::readBig<uint16_t>(in);
    }
    
    // ---
    
    tx1 = new float[numChars];
    ty1 = new float[numChars];
    tx2 = new float[numChars];
    ty2 = new float[numChars];
    
    atlasWidth = DataStreamIO::readBig<uint16_t>(in);
    atlasHeight = DataStreamIO::readBig<uint16_t>(in);
    atlasData = new char[atlasWidth * atlasHeight];
    
    for (int i = 0; i < numChars; i++)
    {
        int cc = DataStreamIO::readBig<uint16_t>(in);
        int left = DataStreamIO::readBig<uint16_t>(in);
        int top = DataStreamIO::readBig<uint16_t>(in);
        
        size_t size = w[cc] * h[cc];
        char *data = new char[size];
        in.read(data, size);
        atlasAddUnit(data, cc, left, top);
        delete[] data;
    }

    // ---
    
    anisotropyAvailable = strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic");
    if (anisotropyAvailable)
    {
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
    }

    // --- TEXTURE INITIALIZATION
    
    glGenTextures(1, &name);
    glBindTexture(GL_TEXTURE_2D, name);

    if (useMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    if (useMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, atlasWidth, atlasHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, atlasData);
    
    if (useMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
    }
    
    delete[] atlasData;
    
    // ---
    
    init();
}

void XFont::init()
{
    matrix.setToIdentity();
    began = 0;
    sequence = NULL;
    setSize(1);
    
    // --- BUFFER ALLOCATION
    
    vertice = new GLfloat[charactersPerSlot * maxDimensions * 4];
    coords = new GLfloat[charactersPerSlot * 2 * 4];
    indices = new GLshort[charactersPerSlot * 6];
    
    GLshort *tmp = indices;
    int offset = 0;
    
    for (int i = 0; i < charactersPerSlot; i++)
    {
        *tmp++ = offset;
        *tmp++ = offset + 1;
        *tmp++ = offset + 2;
        *tmp++ = offset + 2;
        *tmp++ = offset + 3;
        *tmp++ = offset;
        offset += 4;
    }
}

// ---

void XFont::atlasAddUnit(char *srcData, int cc, int left, int top)
{
    char *dstData = atlasData;
    int width = atlasWidth;
    int height = atlasHeight;
    
    int w1 = w[cc];
    int h1 = h[cc];
    
    tx1[cc] = left / (float) width;
    ty1[cc] = top / (float) height;
    tx2[cc] = (left + w1) / (float) width;
    ty2[cc] = (top + h1) / (float) height;
    
    for (int iy = 0; iy < h1; iy++)
    {
        for (int ix = 0; ix < w1; ix++)
        {
            dstData[(iy + top) * width + ix + left] = srcData[iy * w1 + ix];
        }
    }
}

int XFont::binarySearch(int value)
{
    int left = 0;
    int right = lookup16Len - 1;
    
    while (left <= right)
    {
        int mid = (left + right) >> 1;
        if (value > ordered16bits[mid])
        {
            left = mid + 1;
        }
        else if (value < ordered16bits[mid])
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    
    return -1; // NOT FOUND
}

// ---

bool XFont::isValid(wchar_t c)
{
    if (c > 0x1f)
    {
        if (c > 0xff)
        {
            return (binarySearch(c) >= 0);
        }
        else
        {
            return (lookup8bits[c - '!'] >= 0);
        }
    }
    
    return false;
}

int XFont::lookup(wchar_t c)
{
    if (c > 0x1f && !isSpace(c))
    {
        if (c > 0xff)
        {
            int index = binarySearch(c);
            if (index < 0)
            {
                return lookup8bits['?' - '!']; // XXX
            }
            else
            {
                return lookup16bits[index];
            }
        }
        else
        {
            int index = lookup8bits[c - '!'];
            if (index < 0)
            {
                return lookup8bits['?' - '!']; // XXX
            }
            else
            {
                return index;
            }
        }
    }
    
    return -1;
}

// ---

float XFont::getSize()
{
    return size;
}

void XFont::setSize(float size)
{
    this->size = size;
    sizeRatio = size / nativeFontSize;
}

float XFont::getCharWidth(wchar_t c)
{
    if (isSpace(c))
    {
        return spaceWidth * sizeRatio;
    }
    
    if (c > 0x1f)
    {
        if (c > 0xff)
        {
            int index = binarySearch(c);
            if (index < 0)
            {
                return lw[lookup8bits['?' - '!']] * sizeRatio; // XXX
            }
            else
            {
                return lw[lookup16bits[index]] * sizeRatio;
            }
        }
        else
        {
            int index = lookup8bits[c - '!'];
            if (index < 0)
            {
                return lw[lookup8bits['?' - '!']] * sizeRatio; // XXX
            }
            else
            {
                return lw[index] * sizeRatio;
            }
        }
    }
    
    return 0;
}

float XFont::getStringWidth(const wstring &s)
{
    return getSubStringWidth(s, 0, s.size());
}

float XFont::getSubStringWidth(const wstring &s, int begin, int end)
{
    float width = 0;

    for (int i = begin; i < end; i++)
    {
        width += getCharWidth(s.at(i));
    }

    return width;
}

float XFont::getHeight()
{
    return height * sizeRatio;
}

float XFont::getMaxAscent()
{
    return maxAscent * sizeRatio;
}

float XFont::getMaxDescent()
{
    return maxDescent * sizeRatio;
}

float XFont::getStrikethroughOffset()
{
    return strikethroughOffset * sizeRatio;
}

FontMatrix* XFont::getMatrix()
{
    return &matrix;
}

GLshort* XFont::getIndices()
{
    return indices;
}

// --- STATE MANAGEMENT ---

void XFont::begin()
{
    if (began == 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, name);
        
        if (useAnisotropy && anisotropyAvailable)
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    
    began++;
}

void XFont::end()
{
    began--;
    
    if (began == 0)
    {
        if (useAnisotropy && anisotropyAvailable)
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
        }

        glDisable(GL_TEXTURE_2D);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}

// --- BUFFERING ---

void XFont::beginSequence(XFontSequence *seq, int dim)
{
    sequenceDimensions = dim;
    sequenceCount = 0;
    
    if (seq == NULL)
    {
        begin();
    }
    else
    {
        sequence = seq;
        sequence->begin(this, dim);
    }
}

void XFont::endSequence()
{
    if (sequence == NULL)
    {
        flush(sequenceCount);
        end();
    }
    else
    {
        sequence->flush(vertice, coords, sequenceCount);
        sequence->end();
        sequence = NULL;
    }
}

void XFont::flush(int count)
{
    glTexCoordPointer(2, GL_FLOAT, 0, coords);
    glVertexPointer(sequenceDimensions, GL_FLOAT, 0, vertice);
    glDrawElements(GL_TRIANGLES, count * 6, GL_UNSIGNED_SHORT, indices);
}

void XFont::flushIfRequired()
{
    if (sequenceCount == charactersPerSlot)
    {
        if (sequence == NULL)
        {
            flush(sequenceCount);
        }
        else
        {
            sequence->flush(vertice, coords, sequenceCount);
        }
        
        sequenceCount = 0;
    }
}

void XFont::addSequenceCharacter(wchar_t c, float x, float y)
{
    int cc = lookup(c);
    if (cc < 0)
    {
        return;
    }
    
    flushIfRequired();
    
    float x1 = x + le[cc] * sizeRatio;
    float x2 = x1 + w[cc] * sizeRatio;
    float y1 = y + te[cc] * sizeRatio;
    float y2 = y1 - h[cc] * sizeRatio;
    
    GLfloat *tmp = vertice + sequenceCount * 8;
    *tmp++ = x1;
    *tmp++ = y1;
    *tmp++ = x1;
    *tmp++ = y2;
    *tmp++ = x2;
    *tmp++ = y2;
    *tmp++ = x2;
    *tmp   = y1;
    
    tmp = coords + sequenceCount * 8;
    *tmp++ = tx1[cc];
    *tmp++ = ty2[cc];
    *tmp++ = tx1[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp   = ty2[cc];
    
    sequenceCount++;
}

void XFont::addSequenceCharacter(wchar_t c, float x, float y, float z)
{
    int cc = lookup(c);
    if (cc < 0)
    {
        return;
    }
    
    flushIfRequired();
    
    float x1 = x + le[cc] * sizeRatio;
    float x2 = x1 + w[cc] * sizeRatio;
    float y1 = y + te[cc] * sizeRatio;
    float y2 = y1 - h[cc] * sizeRatio;
    
    GLfloat *tmp = vertice + sequenceCount * 12;
    *tmp++ = x1;
    *tmp++ = y1;
    *tmp++ = z;
    *tmp++ = x1;
    *tmp++ = y2;
    *tmp++ = z;
    *tmp++ = x2;
    *tmp++ = y2;
    *tmp++ = z;
    *tmp++ = x2;
    *tmp++ = y1;
    *tmp   = z;
    
    tmp = coords + sequenceCount * 8;
    *tmp++ = tx1[cc];
    *tmp++ = ty2[cc];
    *tmp++ = tx1[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp   = ty2[cc];
    
    sequenceCount++;
}

void XFont::addTransformedEntity(int cc, float x, float y)
{
    flushIfRequired();
    
    float x1 = x + le[cc] * sizeRatio;
    float x2 = x1 + w[cc] * sizeRatio;
    float y1 = y + te[cc] * sizeRatio;
    float y2 = y1 - h[cc] * sizeRatio;
    
    matrix.transform(x1, y2, x2, y1, vertice + sequenceCount * 12);
    
    GLfloat *tmp = coords + sequenceCount * 8;
    *tmp++ = tx1[cc];
    *tmp++ = ty2[cc];
    *tmp++ = tx1[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp   = ty2[cc];
    
    sequenceCount++;
}

void XFont::addTransformedEntity2D(int cc, float x, float y)
{
    flushIfRequired();
    
    float x1 = x + le[cc] * sizeRatio;
    float x2 = x1 + w[cc] * sizeRatio;
    float y1 = y + te[cc] * sizeRatio;
    float y2 = y1 - h[cc] * sizeRatio;
    
    matrix.transform2D(x1, y2, x2, y1, vertice + sequenceCount * 8);
    
    GLfloat *tmp = coords + sequenceCount * 8;
    *tmp++ = tx1[cc];
    *tmp++ = ty2[cc];
    *tmp++ = tx1[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp++ = ty1[cc];
    *tmp++ = tx2[cc];
    *tmp   = ty2[cc];
    
    sequenceCount++;
}
