#include "Sprite.h"

void Sprite::draw(float rx, float ry, bool originUp)
{
    float x1;
    float y1;
    
    if (rotated)
    {
        x1 = -ry + oy;
        y1 = -rx + ox;
    }
    else
    {
        x1 = -rx + ox;
        y1 = -ry + oy;
    }
    
    float x2 = x1 + width;
    float y2 = y1 + height;
    
    GLfloat vertices[4][2];
    GLfloat coords[4][2];
    
    if (rotated)
    {
        vertices[0][0] = y1; vertices[0][1] = x2;
        vertices[1][0] = y2; vertices[1][1] = x2;
        vertices[2][0] = y2; vertices[2][1] = x1;
        vertices[3][0] = y1; vertices[3][1] = x1;
        
        coords[0][0] = originUp ? tx1 : tx2; coords[0][1] = ty1;
        coords[1][0] = originUp ? tx1 : tx2; coords[1][1] = ty2;
        coords[2][0] = originUp ? tx2 : tx1; coords[2][1] = ty2;
        coords[3][0] = originUp ? tx2 : tx1; coords[3][1] = ty1;
    }
    else
    {
        vertices[0][0] = x1; vertices[0][1] = y1;
        vertices[1][0] = x2; vertices[1][1] = y1;
        vertices[2][0] = x2; vertices[2][1] = y2;
        vertices[3][0] = x1; vertices[3][1] = y2;
        
        coords[0][0] = tx1; coords[0][1] = originUp ? ty1 : ty2;
        coords[1][0] = tx2; coords[1][1] = originUp ? ty1 : ty2;
        coords[2][0] = tx2; coords[2][1] = originUp ? ty2 : ty1;
        coords[3][0] = tx1; coords[3][1] = originUp ? ty2 : ty1;
    }
    
    glTexCoordPointer(2, GL_FLOAT, 0, coords);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);    
}
