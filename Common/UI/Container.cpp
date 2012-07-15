#include "Container.h"

using namespace std;
using namespace ci;

namespace chronotext
{
    void Container::setWidth(float newWidth)
    {
        if (autoWidth || newWidth != width)
        {
            updateRequest = true;
            Shape::setWidth(newWidth);
        }
    }
    
    void Container::setHeight(float newHeight)
    {
        if (autoHeight || newHeight != height)
        {
            updateRequest = true;
            Shape::setHeight(newHeight);
        }
    }
    
    void Container::setAutoWidth(bool newAuto)
    {
        if (newAuto != autoWidth)
        {
            updateRequest = true;
            Shape::setAutoWidth(newAuto);
        }
    }
    
    void Container::setAutoHeight(bool newAuto)
    {
        if (newAuto != autoHeight)
        {
            updateRequest = true;
            Shape::setAutoHeight(newAuto);
        }
    }
    
    void Container::setPadding(float left, float top, float right, float bottom)
    {
        updateRequest = true;
        Shape::setPadding(left, top, right, bottom);
    }
    
    float Container::getWidth()
    {
        layout();
        return width;
    }
    
    float Container::getHeight()
    {
        layout();
        return height;
    }
    
    void Container::addComponent(ShapeRef component)
    {
        updateRequest = true;
        components.push_back(component);
    }
    
    void Container::draw()
    {
        layout();

        for (vector<ShapeRef>::const_iterator it = components.begin(); it != components.end(); ++it)
        {
            (*it)->draw();
        }
    }
}
