#pragma once

#include "TextureAtlas.h"

#include <vector>

class TextureAtlasAnimation
{
    std::vector<Sprite*> sprites;

public:
    float fps;
    bool looping;

    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path);
    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path, float fps, bool looping);
    TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path, float fps, bool looping, int firstFrameIndex, int lastFrameIndex);
    
    int getFrameCount();
    float getDuration();

    void drawFromCenter(int frameIndex, bool originUp = true);
    void drawFromCenter(float t, bool originUp = true);
    void playFromCenter(double now, bool originUp = true);
    
    void draw(int frameIndex, float rx = 0, float ry = 0, bool originUp = true);
    void draw(float t, float rx = 0, float ry = 0, bool originUp = true);
    void play(double now, float rx = 0, float ry = 0, bool originUp = true);
};
