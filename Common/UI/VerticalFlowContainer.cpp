#include "VerticalFlowContainer.h"

using namespace std;
using namespace ci;

namespace chronotext
{
    void VerticalFlowContainer::layout()
    {
        if (updateRequest)
        {
            float innerWidth = width - paddingLeft - paddingRight;
            float innerHeight = 0;
            float previousMargin = paddingTop;
            float xx = x + paddingLeft;
            
            contentWidth = 0;
            contentHeight = 0;
            
            for (vector<ShapeRef>::const_iterator it = components.begin(); it != components.end(); ++it)
            {
                ShapeRef shape = *it;
                
                innerHeight += fmaxf(previousMargin, shape->marginTop);
                shape->setLocation(xx, y + innerHeight);
                
                if (!shape->autoWidth)
                {
                    if (autoWidth)
                    {
                        throw runtime_error("VerticalFlowContainer WITH UNDEFINED-WIDTH MUST CONTAIN COMPONENTS WITH FIXED-WIDTH");
                    }
                    else
                    {
                        shape->setWidth(innerWidth);
                    }
                }
                
                contentWidth = fmaxf(contentWidth, shape->getWidth());
                contentHeight += shape->getHeight();
                
                innerHeight += shape->getHeight();
                previousMargin = shape->marginBottom;
            }
            
            innerHeight += fmaxf(previousMargin, paddingBottom);
            
            if (autoWidth)
            {
                width = paddingLeft + contentWidth + paddingRight;
            }
            
            if (autoHeight)
            {
                height = innerHeight;
            }
        }
        
        updateRequest = false;
    }
}
