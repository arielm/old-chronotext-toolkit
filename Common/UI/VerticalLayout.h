#pragma once

#include "Container.h"

/*
 * LIMITATIONS:
 * 1) COMPONENTS WITH FIXED-WIDTH RECEIVE THE WIDTH OF THE VerticalLayout
 * 2) COMPONENTS WITH UNDEFINED-WIDTH CAN'T BE LAYED-OUT WHEN THE WIDTH OF THE VerticalLayout IS UNDEFINED
 *
 * TODO:
 * 1) FIX LIMITATION 1
 * 2) HANDLE HORIZONTAL AND VERTICAL ALIGNMENT
 * 3) HANDLE CONTENT-OVERFLOW
 */

namespace chronotext
{
    class VerticalLayout : public Container
    {
    protected:
        float contentWidth;
        float contentHeight;

    public:
        VerticalLayout() : Container() {}

        VerticalLayout(ShapeStyleRef style)
        :
        Container(style)
        {}
        
        void layout();
    };
}

namespace chr = chronotext;
