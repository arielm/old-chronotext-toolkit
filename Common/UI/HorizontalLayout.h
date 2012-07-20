#pragma once

#include "Container.h"
#include "LayoutStyle.h"

/*
 * TODO:
 * 1) HANDLE CONTENT-OVERFLOW
 */

namespace chronotext
{
    class HorizontalLayout : public Container
    {
    protected:
        float contentWidth;
        float contentHeight;

    public:
        int alignX;
        int alignY;

        HorizontalLayout() : Container() {}

        HorizontalLayout(LayoutStyleRef style)
        :
        Container(style),
        alignX(style->alignX),
        alignY(style->alignY)
        {}
        
        void setAlign(int x, int y);

        void layout();
    };
}

namespace chr = chronotext;
