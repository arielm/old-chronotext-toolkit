#pragma once

#include "Container.h"

/*
 * LIMITATIONS:
 * 1) COMPONENTS WITH FIXED-WIDTH RECEIVE THE WIDTH OF THE VerticalFlowContainer
 * 2) COMPONENTS WITH UNDEFINED-WIDTH CAN'T BE LAYED-OUT WHEN THE WIDTH OF THE VerticalFlowContainer IS UNDEFINED
 *
 * TODO:
 * 1) FIX LIMITATION 1
 * 2) HANDLE HORIZONTAL AND VERTICAL ALIGNMENT
 * 3) HANDLE CONTENT-OVERFLOW
 */

namespace chronotext
{
    class VerticalFlowContainer : public Container
    {
    protected:
        float contentWidth;
        float contentHeight;

    public:
        VerticalFlowContainer() : Container() {}

        VerticalFlowContainer(ShapeStyleRef style)
        :
        Container(style)
        {}
        
        void layout();
    };
}

namespace chr = chronotext;
