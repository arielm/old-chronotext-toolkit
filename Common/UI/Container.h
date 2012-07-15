#pragma once

#include "Shape.h"

namespace chronotext
{
    class Container : public Shape
    {
    protected:
        bool updateRequest;

    public:
        std::vector<ShapeRef> components;

        Container() : Shape() {}

        Container(ShapeStyleRef style)
        :
        Shape(style),
        updateRequest(false)
        {}
        
        void setWidth(float newWidth);
        void setHeight(float newHeight);
        void setAutoWidth(bool newAuto);
        void setAutoHeight(bool newAuto);
        void setPadding(float left, float top, float right, float bottom);
        
        float getWidth();
        float getHeight();

        void addComponent(ShapeRef component);
        
        virtual void layout() = 0;
        void draw();
    };
}

namespace chr = chronotext;
