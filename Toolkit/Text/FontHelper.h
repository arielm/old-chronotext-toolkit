#pragma once

#include "WordWrapper.h"
#include "FollowablePath.h"

class FontHelper
{
public:
    static void drawText(XFont *font, const std::wstring &text, float x, float y, bool snap = false)
    {
        int len = text.size();
        
        if (snap)
        {
            x = floorf(x);
            y = floorf(y);
        }
        
        font->beginSequence(NULL, 2);
        
        for (int i = 0; i < len; i++)
        {
            wchar_t ch = text.at(i);
            font->addSequenceCharacter(ch, x, y);
            
            float ww = font->getCharWidth(ch);
            x += snap ? rintf(ww) : ww;
        }
        
        font->endSequence();
    }

    static void drawText(XFont *font, const std::wstring &text, float x, float y1, float y2, bool snap = false)
    {
        float h = y2 - y1;
        float y = y1 + h / 2 - font->getStrikethroughOffset();
        
        drawText(font, text, x, y, snap);
    }
    
    static void drawText(XFont *font, const std::wstring &text, float x1, float y1, float x2, float y2, bool snap = false)
    {
        float w = x2 - x1;
        float x = x1 + (w - getStringWidth(font, text, snap)) / 2;
        
        drawText(font, text, x, y1, y2, snap);
    }
    
    static float getStringWidth(XFont *font, const std::wstring &text, bool snap = false)
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

    static float drawTextOnPath(XFont *font, const std::wstring &text, FollowablePath *path, float offset)
    {
        float res[3];
        
        int len = text.size();
        float offsetX = offset;
        float offsetY = font->getMaxDescent();
        float sampleSize = font->getSize() / 2;
        
        FontMatrix *matrix = font->getMatrix();
        font->beginSequence(NULL, 2);
        
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
    
    static void drawWrappedText(XFont *font, const std::wstring &text, WordWrapper *wrapper, float x, float y, float lineHeight)
    {
        float yy = y + font->getMaxAscent();
        
        font->beginSequence(NULL, 2);
        
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
};
