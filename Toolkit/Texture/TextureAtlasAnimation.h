#pragma once

#include "TextureAtlas.h"

#include <vector>

class TextureAtlasAnimation
{
    TextureAtlas *atlas;
    std::vector<Sprite*> sprites;

public:
    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path);
    
    int getFrameCount();

    void drawFromCenter(int frameIndex, bool originUp = true);
    void drawFromCenter(float t, bool originUp = true);
    
    void draw(int frameIndex, float rx = 0, float ry = 0, bool originUp = true);
    void draw(float t, float rx = 0, float ry = 0, bool originUp = true);
};
