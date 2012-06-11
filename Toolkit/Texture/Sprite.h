/*
 * WORKS WITH TextureAtlas
 */

#pragma once

class Sprite
{
public:
    float width;
    float height;
    float ox;
    float oy;
    float ow;
    float oh;
    bool rotated;

    float tx1;
    float ty1;
    float tx2;
    float ty2;
    
    Sprite() {}

    Sprite(float width, float height, float ox, float oy, float ow, float oh, bool rotated, float tx1, float ty1, float tx2, float ty2)
    :
    width(width),
    height(height),
    ox(ox),
    oy(oy),
    ow(ow),
    oh(oh),
    rotated(rotated),
    tx1(tx1),
    ty1(ty1),
    tx2(tx2),
    ty2(ty2)
    {}
    
    void draw(float rx = 0, float ry = 0, bool originUp = true);
};
