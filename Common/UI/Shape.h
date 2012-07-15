#pragma once

#include "Touchable.h"
#include "ShapeStyle.h"

#include "cinder/Vector.h"
#include "cinder/Rect.h"

namespace chronotext
{
    typedef boost::shared_ptr<class Shape> ShapeRef;

    class Shape
    {
    public:
        enum
        {
            ALIGN_LEFT,
            ALIGN_RIGHT,
            ALIGN_TOP,
            ALIGN_BOTTOM,
            ALIGN_MIDDLE
        };
        
        float x;
        float y;

        float width;
        float height;
        
        bool autoWidth;
        bool autoHeight;
        
        bool visible;
        
        float paddingLeft;
        float paddingTop;
        float paddingRight;
        float paddingBottom;

        float marginLeft;
        float marginTop;
        float marginRight;
        float marginBottom;
        
        Shape() {}
        Shape(ShapeStyleRef style);
        
        void setLocation(float x, float y);
        virtual void setWidth(float newWidth);
        virtual void setHeight(float newHeight);
        virtual void setAutoWidth(bool newAuto);
        virtual void setAutoHeight(bool newAuto);
        virtual void setBounds(const ci::Rectf &bounds);
        virtual void setPadding(float left, float top, float right, float bottom);
        void setMargin(float left, float top, float right, float bottom);
        
        ci::Vec2f getLocation();
        virtual float getWidth();
        virtual float getHeight();
        virtual ci::Rectf getBounds();
        
        virtual void draw() {};
        
        virtual std::vector<Touchable*> getTouchables();
        virtual void touchStateChanged(Touchable *touchable, int state) {}
        virtual void touchActionPerformed(Touchable *touchable, int action) {}
    };
}

namespace chr = chronotext;
