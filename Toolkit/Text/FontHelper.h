#pragma once

#include "WordWrapper.h"
#include "FollowablePath.h"

class FontHelper
{
public:
    enum
    {
        ALIGN_LEFT,
        ALIGN_RIGHT,
        ALIGN_TOP,
        ALIGN_BOTTOM,
        ALIGN_MIDDLE
    };

    static float getStringWidth(XFont *font, const std::wstring &text, bool snap = false);

    static void drawText(XFont *font, XFontSequence *sequence, const std::wstring &text, float x = 0, float y = 0, bool snap = false);
    static void drawAlignedText(XFont *font, XFontSequence *sequence, const std::wstring &text, float x = 0, float y = 0, int alignX = ALIGN_MIDDLE, int alignY = ALIGN_MIDDLE, bool snap = false);
    static void drawTextInRect(XFont *font, XFontSequence *sequence, const std::wstring &text, float x1, float y1, float x2, float y2, bool snap = false);
    static void drawStrikethroughInRect(XFont *font, const std::wstring &text, float x1, float y1, float x2, float y2, bool snap = false);
    
    static float drawTextOnPath(XFont *font, XFontSequence *sequence, const std::wstring &text, FollowablePath *path, float offset);
    static void drawWrappedText(XFont *font, XFontSequence *sequence, const std::wstring &text, WordWrapper *wrapper, float x, float y, float lineHeight);
};
