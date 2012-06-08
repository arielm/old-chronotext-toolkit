#pragma once

#include "XFont.h"

#include <vector>

class TextLayout
{
    void addLine(std::wstring *text, int offset, int length);
    
public:
    XFont *font;
    std::wstring *text;

    int size;
    std::vector<int> offsets;
    std::vector<int> lengths;
    
    TextLayout() {}
    TextLayout(XFont *font, std::wstring *text) : font(font), text(text) {}
    
    float wrap();
    void wrap(float width);
    
    void draw(float x, float y);
};
