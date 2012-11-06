#include "chronotext/texture/TextureAtlasManager.h"
#include "chronotext/texture/TextureHelper.h"

using namespace ci;
using namespace std;

TextureAtlasManager::~TextureAtlasManager()
{
    for (map<int, TextureAtlas*>::iterator it = atlases.begin(); it != atlases.end(); ++it)
    {
        delete it->second;
    }
}

void TextureAtlasManager::setAtlas(const string &resourceName, int index, bool useMipmap)
{
    atlases[index] = new TextureAtlas(InputSource::loadResource(resourceName), useMipmap);
}

TextureAtlas* TextureAtlasManager::getAtlas(int index)
{
    return atlases[index];
}

void TextureAtlasManager::beginTexture(int index)
{
    atlases[index]->beginTexture();
}

void TextureAtlasManager::endTexture()
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void TextureAtlasManager::unload()
{
    for (map<int, TextureAtlas*>::iterator it = atlases.begin(); it != atlases.end(); ++it)
    {
        it->second->unload();
    }
}

void TextureAtlasManager::reload()
{
    for (map<int, TextureAtlas*>::iterator it = atlases.begin(); it != atlases.end(); ++it)
    {
        it->second->reload();
    }
}
