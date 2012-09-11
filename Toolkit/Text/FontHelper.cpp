#include "FontHelper.h"

using namespace std;
using namespace ci;

void FontHelper::drawText(XFont *font, XFontSequence *sequence, const wstring &text, float x, float y, int alignX, int alignY)
{
    int len = text.size();

    float xx = x;
    float yy = y;

    switch (alignX)
    {
        case ALIGN_MIDDLE:
            xx -= font->getStringWidth(text) / 2;
            break;
            
        case ALIGN_RIGHT:
            xx -= font->getStringWidth(text);
            break;
    }
    
    switch (alignY)
    {
        case ALIGN_TOP:
            yy += font->getMaxDescent();
            break;
            
        case ALIGN_MIDDLE:
            yy -= font->getStrikethroughOffset();
            break;
    }
    
    font->beginSequence(sequence, 2);
    
    for (int i = 0; i < len; i++)
    {
        wchar_t ch = text.at(i);
        font->addSequenceCharacter(ch, xx, yy);
        
        xx += font->getCharWidth(ch);
    }
    
    font->endSequence();
}
