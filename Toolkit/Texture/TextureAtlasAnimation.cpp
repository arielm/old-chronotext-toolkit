#include "TextureAtlasAnimation.h"

using namespace std;

TextureAtlasAnimation::TextureAtlasAnimation(TextureAtlas *atlas, const string &path) : fps(24)
{
    sprites = atlas->getAnimationSprites(path);
}

TextureAtlasAnimation::TextureAtlasAnimation(TextureAtlas *atlas, const string &path, float fps) : fps(fps)
{
    sprites = atlas->getAnimationSprites(path);
}

TextureAtlasAnimation::TextureAtlasAnimation(TextureAtlas *atlas, const string &path, int firstFrameIndex, int lastFrameIndex, float fps) : fps(fps)
{
    vector<Sprite*> tmp = atlas->getAnimationSprites(path);
    
    if (((firstFrameIndex < 0) || (firstFrameIndex >= tmp.size()) || ((lastFrameIndex <0) || (lastFrameIndex >= tmp.size()))))
    {
        throw std::runtime_error ("OUT-OF-RANGE ANIMATION FRAMES");
    }
    
    if (firstFrameIndex < lastFrameIndex)
    {
        for (int i = firstFrameIndex; i <= lastFrameIndex; i++)
        {
            sprites.push_back(tmp[i]);
        }
    }
    else
    {
        for (int i = firstFrameIndex; i >= lastFrameIndex; i--)
        {
            sprites.push_back(tmp[i]);
        }
    }
}

int TextureAtlasAnimation::getFrameCount()
{
    return sprites.size();
}

float TextureAtlasAnimation::getDuration()
{
    return sprites.size() / fps;
}

void TextureAtlasAnimation::drawFromCenter(int frameIndex, bool originUp)
{
    Sprite *sprite = sprites[frameIndex % sprites.size()];
    sprite->drawFromCenter(originUp);
}

void TextureAtlasAnimation::drawFromCenter(float t, bool originUp)
{
    int frameIndex = t * sprites.size();
    drawFromCenter(frameIndex, originUp);
}

void TextureAtlasAnimation::playFromCenter(double now, bool originUp)
{
    float t = fmodf(now / getDuration(), 1);
    drawFromCenter(t, originUp);
}

void TextureAtlasAnimation::draw(int frameIndex, float rx, float ry, bool originUp)
{
    Sprite *sprite = sprites[frameIndex % sprites.size()];
    sprite->draw(rx, ry, originUp);
}

void TextureAtlasAnimation::draw(float t, float rx, float ry, bool originUp)
{
    int frameIndex = t * sprites.size();
    draw(frameIndex, originUp);
}

void TextureAtlasAnimation::play(double now, float rx, float ry, bool originUp)
{
    float t = fmodf(now / getDuration(), 1);
    draw(t, rx, ry, originUp);
}
