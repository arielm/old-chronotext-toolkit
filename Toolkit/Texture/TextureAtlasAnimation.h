#pragma once

#include "TextureAtlas.h"

#include <vector>

class TextureAtlasAnimation
{
    std::vector<Sprite*> sprites;
    float fps;

public:
    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path);
    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path, float fps);
    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path, int firstFrameIndex, int lastFrameIndex, float fps);
    
    int getFrameCount();
    float getDuration();

    void drawFromCenter(int frameIndex, bool originUp = true);
    void drawFromCenter(float t, bool originUp = true);
    void playFromCenter(double now, bool originUp = true);
    
    void draw(int frameIndex, float rx = 0, float ry = 0, bool originUp = true);
    void draw(float t, float rx = 0, float ry = 0, bool originUp = true);
    void play(double now, float rx = 0, float ry = 0, bool originUp = true);
};
