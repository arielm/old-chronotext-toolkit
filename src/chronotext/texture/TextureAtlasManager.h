#pragma once

#include "chronotext/texture/TextureAtlas.h"

class TextureAtlasManager
{
    std::vector<TextureAtlas*> atlases;

public:
    ~TextureAtlasManager();
    
    void addAtlas(const std::string &resourceName, bool useMipmap = false);
    TextureAtlas* getAtlas(int index);

    void beginTexture(int index);
    void endTexture();
    
    void unload();
    void reload();
};
