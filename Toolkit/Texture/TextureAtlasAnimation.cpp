#include "TextureAtlasAnimation.h"

TextureAtlasAnimation::TextureAtlasAnimation(TextureAtlas *atlas, const std::string &pattern) : atlas(atlas)
{
    sprites = atlas->getAnimationSprites(pattern);
}

int TextureAtlasAnimation::getFrameCount()
{
    return sprites.size();
}

void TextureAtlasAnimation::draw(int frameIndex)
{
    Sprite *sprite = sprites[frameIndex % sprites.size()];
    sprite->draw(sprite->ow / 2, sprite->oh / 2);
}
