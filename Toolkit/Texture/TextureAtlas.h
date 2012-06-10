/*
 * MANAGING SPRITES FROM TEXTURE-ATLAS MADE WITH TexturePacker
 */

#pragma once

#include "TextureHelper.h"
#include "Sprite.h"

#include "cinder/DataSource.h"

#include <map>

class TextureAtlas
{
    std::string texturePath;
    
    float width;
    float height;
    
    std::map<std::string, Sprite> sprites;

public:
    ci::gl::Texture *texture;

    TextureAtlas(ci::DataSourceRef dataSource);    
    ~TextureAtlas();
    
    void clear();
    void reload();

    Sprite getSprite(const std::string &path);
    void drawSprite(const std::string &path, float rx = 0, float ry = 0, bool originUp = true);
};
