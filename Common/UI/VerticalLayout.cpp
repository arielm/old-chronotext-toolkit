#include "VerticalLayout.h"

using namespace std;
using namespace ci;

namespace chronotext
{
    void VerticalLayout::layout()
    {
        if (layoutRequest)
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
                
                if (shape->visible)
                {
                    innerHeight += mergedMargin(previousMargin, shape->marginTop);
                    shape->setLocation(xx, y + innerHeight);
                    
                    if (!shape->autoWidth)
                    {
                        if (autoWidth)
                        {
                            throw runtime_error("VerticalLayout WITH UNDEFINED-WIDTH MUST CONTAIN COMPONENTS WITH FIXED-WIDTH");
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
            }
            
            innerHeight += mergedMargin(previousMargin, paddingBottom);
            
            if (autoWidth)
            {
                width = paddingLeft + contentWidth + paddingRight;
            }
            
            if (autoHeight)
            {
                height = innerHeight;
            }
        }
        
        layoutRequest = false;
    }
}
