#pragma once

#include "cinder/gl/gl.h"

class GraphicHelper
{
public:
    static void fillBox(float x1, float y1, float x2, float y2)
    {
        const GLfloat vertices[] =
        {
            x1, y1,
            x2, y1,
            x2, y2,
            x1, y2
        };
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};
