#include "TextureAtlasAnimation.h"

TextureAtlasAnimation::TextureAtlasAnimation(TextureAtlas *atlas, const std::string &path) : atlas(atlas)
{
    sprites = atlas->getAnimationSprites(path);
}

int TextureAtlasAnimation::getFrameCount()
{
    return sprites.size();
}

void TextureAtlasAnimation::draw(int frameIndex, bool originUp)
{
    Sprite *sprite = sprites[frameIndex % sprites.size()];
    sprite->drawFromCenter(originUp);
}