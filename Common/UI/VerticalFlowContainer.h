#pragma once

#include "Container.h"

/*
 * LIMITATIONS:
 * - COMPONENTS WITH FIXED-WIDTH RECEIVE THE WIDTH OF THE VerticalFlowContainer
 * - COMPONENTS WITH UNDEFINED-WIDTH CAN'T BE LAYED-OUT WHEN THE WIDTH OF THE VerticalFlowContainer IS UNDEFINED
 */

namespace chronotext
{
    class VerticalFlowContainer : public Container
    {
    protected:
        float contentWidth;
        float contentHeight;
        
        float mergedMargin(float previousMargin, float nextMargin);

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
