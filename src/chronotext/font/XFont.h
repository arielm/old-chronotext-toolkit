#pragma once

#include "chronotext/InputSource.h"
#include "chronotext/font/FontMatrix.h"
#include "chronotext/font/XFontSequence.h"

#include "cinder/gl/gl.h"

typedef boost::shared_ptr<class XFont> XFontRef;

class XFont
{
protected:
    int numChars;
    float *w;
    float *h;
    float *le;
    float *te;
    float *lw;
    
    float nativeFontSize;
    float spaceWidth;
    float height;
    float maxAscent;
    float maxDescent;
    float strikethroughOffset;

    int *lookup8bits;
    int *lookup16bits;
    int *ordered16bits;
    
    int lookup8Len;
    int lookup16Len;
    
    float *tx1;
    float *ty1;
    float *tx2;
    float *ty2;
    
    bool anisotropyAvailable;
    float maxAnisotropy;
    
    GLuint name;

private:
    int atlasWidth, atlasHeight;
    char *atlasData;

    bool useMipmap;
    bool useAnisotropy;
    int maxDimensions;
    int charactersPerSlot;
    
    float size;
    float sizeRatio;
    int began;
    FontMatrix matrix;
    
    GLfloat *vertice;
    GLfloat *coords;
    GLshort *indices;
    
    int sequenceCount;
    int sequenceDimensions;
    XFontSequence *sequence;
    
    void atlasAddUnit(char *srcData, int cc, int left, int top);
    int binarySearch(int value);

    void init();
    void read(InputSourceRef inputSource);
    void readFromStream(std::istream &in);

    void flush(int count);
    void flushIfRequired();

public:
    XFont(InputSourceRef inputSource, bool useMipmap, bool useAnisotropy, int maxDimensions, int charactersPerSlot);
    ~XFont();
    
    bool isValid(wchar_t c);
    int lookup(wchar_t c);
    
    float getSize();
    void setSize(float size);
    
    float getCharWidth(wchar_t c);
    float getStringWidth(const std::wstring &s);
    float getSubStringWidth(const std::wstring &s, int begin, int end);
    float getHeight();
    float getMaxAscent();
    float getMaxDescent();
    float getStrikethroughOffset();
    FontMatrix* getMatrix();
    GLshort* getIndices();
    
    void begin();
    void end();
    
    void beginSequence(XFontSequence *seq, int dim);
    void endSequence();
    void addSequenceCharacter(wchar_t c, float x, float y);
    void addSequenceCharacter(wchar_t c, float x, float y, float z);
    void addTransformedEntity(int cc, float x, float y);
    void addTransformedEntity2D(int cc, float x, float y);
};
