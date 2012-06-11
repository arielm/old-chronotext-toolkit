#pragma once

#include "TextureAtlas.h"

#include <vector>

class TextureAtlasAnimation
{
    TextureAtlas *atlas;
    std::vector<Sprite*> sprites;

public:
    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &pattern);
    
    int getFrameCount();
    void draw(int frameIndex);
};
