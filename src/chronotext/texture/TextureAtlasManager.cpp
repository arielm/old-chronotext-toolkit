#include "chronotext/texture/TextureAtlasManager.h"
#include "chronotext/texture/TextureHelper.h"

using namespace ci;
using namespace std;

TextureAtlasManager::~TextureAtlasManager()
{
    for (vector<TextureAtlas*>::iterator it = atlases.begin(); it != atlases.end(); ++it)
    {
        delete *it;
    }
}

void TextureAtlasManager::addAtlas(const string &resourceName, bool useMipmap)
{
    atlases.push_back(new TextureAtlas(InputSource::loadResource(resourceName), useMipmap));
}

TextureAtlas* TextureAtlasManager::getAtlas(int index)
{
    return atlases.at(index);
}

void TextureAtlasManager::beginTexture(int index)
{
    atlases.at(index)->beginTexture();
}

void TextureAtlasManager::endTexture()
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void TextureAtlasManager::unload()
{
    for (vector<TextureAtlas*>::iterator it = atlases.begin(); it != atlases.end(); ++it)
    {
        (*it)->unload();
    }
}

void TextureAtlasManager::reload()
{
    for (vector<TextureAtlas*>::iterator it = atlases.begin(); it != atlases.end(); ++it)
    {
        (*it)->reload();
    }
}
