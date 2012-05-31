#pragma once

#include "XFont.h"
#include "FollowablePath.h"

class FontHelper
{
public:
    static void drawText(XFont *font, const std::wstring &text, float x, float y, bool snap)
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

    static void drawText(XFont *font, const std::wstring &text, float x, float y1, float y2, bool snap)
    {
        float h = y2 - y1;
        float y = y1 + h / 2 - font->getStrikethroughOffset();
        
        drawText(font, text, x, y, snap);
    }
    
    static void drawText(XFont *font, const std::wstring &text, float x1, float y1, float x2, float y2, bool snap)
    {
        float w = x2 - x1;
        float x = x1 + (w - getStringWidth(font, text, snap)) / 2;
        
        drawText(font, text, x, y1, y2, snap);
    }
    
    static float getStringWidth(XFont *font, const std::wstring &text, bool snap)
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

    static float drawTextOnPath(XFont *font, FollowablePath *path, const std::wstring &text, float offset)
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
};
