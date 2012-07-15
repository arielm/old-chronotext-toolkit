#pragma once

#include "ShapeStyle.h"
#include "XFont.h"

#include "cinder/Color.h"

namespace chronotext
{
    typedef boost::shared_ptr<class TextBoxStyle> TextBoxStyleRef;

    class TextBoxStyle : public ShapeStyle
    {
    public:
        XFont *font;
        float fontSize;
        bool wrap;
        
        float lineHeight;
        float lineHeightFactor;
        
        int textAlignX;
        int textAlignY;
        
        ci::ColorAT<float> textColor;

        TextBoxStyle()
        :
        ShapeStyle(),
        font(NULL),
        fontSize(1),
        wrap(true),
        lineHeight(0),
        lineHeightFactor(1),
        textAlignX(Shape::ALIGN_LEFT),
        textAlignY(Shape::ALIGN_TOP),
        textColor(ci::ColorA(0, 0, 0, 1))
        {}
    };
}

namespace chr = chronotext;
