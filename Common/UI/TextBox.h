/*
 * BASED ON TextBox.java FROM GRAPH PROJECT
 *
 * TODO:
 * - IMPLEMENT CLIPPING
 * - FILL-COLOR AND BORDER-COLOR
 */

#pragma once

#include "Shape.h"
#include "TextBoxStyle.h"
#include "WordWrapper.h"

namespace chronotext
{
    typedef boost::shared_ptr<class TextBox> TextBoxRef;

    class TextBox : public Shape
    {
    protected:
        bool updateWrapRequest;
        bool updateWidthRequest;
        bool updateHeightRequest;
        bool updateLineHeightRequest;
        
        float contentWidth;
        float contentHeight;
        
        float getOffsetX(int start, int end);
        float getOffsetY();
        float getLineTop(int index);
        float getLinesHeight(int n);
        
        void drawText();
        void drawTextSpan(float xx, float yy, int start, int end, float limitLeft, float limitRight);
        
    public:
        XFont *font;
        float fontSize;
        bool wrap;

        float lineHeight;
        float lineHeightFactor;

        int textAlignX;
        int textAlignY;

        ci::ColorAT<float> textColor;

        bool overflowX;
        bool overflowY;
        float offsetX;
        float offsetY;
        
        std::wstring text;
        WordWrapper wrapper;

        TextBox() : Shape() {}
        TextBox(TextBoxStyleRef style);
        
        void setFont(XFont *newFont);
        void setFontSize(float size);
        void setLineHeightFactor(float factor);
        void setLineHeight(float newHeight);
        void setWidth(float newWidth);
        void setHeight(float newHeight);
        void setAutoWidth(bool newAuto);
        void setAutoHeight(bool newAuto);
        void setPadding(float left, float top, float right, float bottom);
        void setTextAlign(int h, int v);
        void setWrap(bool newWrap);
        void setOffsetX(float x);
        void setOffsetY(float y);
        void setTextColor(const ci::ColorAT<float> &newTextColor);
        virtual void setText(const std::wstring &newText);
        
        float getWidth();
        float getHeight();
        float getLineHeight();
        
        virtual void layout();
        void draw();
        
        ci::Vec2f getLocationAt(int line, int index);
    };
}

namespace chr = chronotext;
