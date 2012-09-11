#include "FontHelper.h"

using namespace std;
using namespace ci;

float FontHelper::getStringWidth(XFont *font, const wstring &text, bool snap)
{
    if (snap)
    {
        float w = 0;
        int len = text.size();
        
        for (int i = 0; i < len; i++)
        {
            wchar_t ch = text.at(i);
            w += rintf(font->getCharWidth(ch));
        }
        
        return w;
    }
    else
    {
        return font->getStringWidth(text);
    }
}

void FontHelper::drawText(XFont *font, XFontSequence *sequence, const wstring &text, float x, float y, bool snap)
{
    int len = text.size();
    
    if (snap)
    {
        x = floorf(x);
        y = floorf(y);
    }
    
    font->beginSequence(sequence, 2);
    
    for (int i = 0; i < len; i++)
    {
        wchar_t ch = text.at(i);
        font->addSequenceCharacter(ch, x, y);
        
        float ww = font->getCharWidth(ch);
        x += snap ? rintf(ww) : ww;
    }
    
    font->endSequence();
}

void FontHelper::drawAlignedText(XFont *font, XFontSequence *sequence, const wstring &text, float x, float y, int alignX, int alignY, bool snap)
{
    switch (alignX)
    {
        case ALIGN_MIDDLE:
            x -= getStringWidth(font, text, snap) / 2;
            break;
            
        case ALIGN_RIGHT:
            x -= getStringWidth(font, text, snap);
            break;
    }
    
    switch (alignY)
    {
        case ALIGN_TOP:
            y += font->getMaxDescent();
            break;
            
        case ALIGN_MIDDLE:
            y -= font->getStrikethroughOffset();
            break;
    }
    
    drawText(font, sequence, text, x, y, snap);
}

void FontHelper::drawTextInRect(XFont *font, XFontSequence *sequence, const std::wstring &text, const Rectf &rect, bool snap)
{
    drawTextInRect(font, sequence, text, rect.x1, rect.y1, rect.x2, rect.y2, snap);
}

void FontHelper::drawTextInRect(XFont *font, XFontSequence *sequence, const wstring &text, float x1, float y1, float x2, float y2, bool snap)
{
    float w = x2 - x1;
    float x = x1 + (w - getStringWidth(font, text, snap)) / 2;
    
    float h = y2 - y1;
    float y = y1 + h / 2 - font->getStrikethroughOffset();
    
    drawText(font, sequence, text, x, y, snap);
}

void FontHelper::drawStrikethroughInRect(XFont *font, const wstring &text, float x1, float y1, float x2, float y2, bool snap)
{
    float w1 = getStringWidth(font, text, snap);
    float w2 = x2 - x1;
    float x3 = x1 + (w2 - w1) / 2;
    float x4 = x3 + w1;
    
    float h = y2 - y1;
    float y3 = y1 + h / 2;
    
    if (snap)
    {
        x3 = floorf(x3);
        x4 = floorf(x4);
        y3 = floorf(y3);
    }
    
    const GLfloat vertices[] =
    {
        x3, y3,
        x4, y3
    };
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

float FontHelper::drawTextOnPath(XFont *font, XFontSequence *sequence, const wstring &text, FollowablePath *path, float offset)
{
    float res[3];
    
    int len = text.size();
    float offsetX = offset;
    float offsetY = font->getMaxDescent();
    float sampleSize = font->getSize() / 2;
    
    FontMatrix *matrix = font->getMatrix();
    font->beginSequence(sequence, 2);
    
    for (int i = 0; i < len; i++)
    {
        wchar_t ch = text.at(i);
        float half = 0.5f * font->getCharWidth(ch);
        offsetX += half;
        
        int cc = font->lookup(ch);
        if (cc > -1)
        {
            path->pos2Point(offsetX, res);
            float theta = path->pos2SampledAngle(offsetX, sampleSize);
            
            matrix->setTranslation(res[0], res[1], 0);
            matrix->rotateZ(theta);
            font->addTransformedEntity2D(cc, -half, offsetY);
        }
        
        offsetX += half;
    }
    
    font->endSequence();
    
    return offsetX;
}

void FontHelper::drawWrappedText(XFont *font, XFontSequence *sequence, const wstring &text, WordWrapper *wrapper, float x, float y, float lineHeight)
{
    float yy = y + font->getMaxAscent();
    
    font->beginSequence(sequence, 2);
    
    for (int j = 0; j < wrapper->size; j++)
    {
        float offset = wrapper->offsets[j];
        float length = wrapper->lengths[j];
        float xx = x;
        
        for (int i = offset; i < offset + length; i++)
        {
            wchar_t c = text.at(i);
            font->addSequenceCharacter(c, xx, yy);
            xx += font->getCharWidth(c);
        }
        
        yy += lineHeight;
    }
    
    font->endSequence();
}
