#pragma once

#include "chronotext/font/XFont.h"

#include <vector>

class WordWrapper
{
    void addLine(std::wstring *text, int offset, int length);
    
public:
    int size;
    std::vector<int> offsets;
    std::vector<int> lengths;
    
    float wrap(XFont *font, std::wstring *text);
    void wrap(XFont *font, std::wstring *text, float width);

    int getLine(int offset);
};
