#pragma once

#include "ShapeStyle.h"
#include "XFont.h"

#include <map>

namespace chronotext
{
    typedef boost::shared_ptr<class ButtonStyle> ButtonStyleRef;

    class ButtonStyle : public ShapeStyle
    {
    public:
        XFont *font;
        float fontSize;
        bool snap;
        
        std::map<int, ColorRef> borderColor;
        std::map<int, ColorRef> backgroundColor;
        std::map<int, ColorRef> color;
        
        float hitExtra;

        ButtonStyle()
        :
        ShapeStyle(),
        font(NULL),
        fontSize(1),
        snap(false),
        hitExtra(8)
        {}
    };
}

namespace chr = chronotext;
