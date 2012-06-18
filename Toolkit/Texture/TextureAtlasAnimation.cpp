#include "TextureAtlasAnimation.h"

TextureAtlasAnimation::TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path) : atlas(atlas)
{
    sprites = atlas->getAnimationSprites(path);
}

int TextureAtlasAnimation::getFrameCount()
{
    return sprites.size();
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
