#pragma once

#include "ShapeStyle.h"
#include "XFont.h"

#include "cinder/Color.h"

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
        
        std::map< int, ci::ColorAT<float> > borderColor;
        std::map< int, ci::ColorAT<float> > backgroundColor;
        std::map< int, ci::ColorAT<float> > color;
        
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
