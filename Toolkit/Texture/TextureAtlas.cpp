#include "TextureAtlas.h"

#include "cinder/app/AppBasic.h"
#include "cinder/Xml.h"

using namespace ci;
using namespace ci::app;
using namespace std;

TextureAtlas::TextureAtlas(DataSourceRef dataSource, bool useMipmap, bool forceToAlpha)
{
    XmlTree doc(dataSource);
    
    const XmlTree textureAtlasElement = doc.getChild("TextureAtlas");
    texturePath = textureAtlasElement.getAttributeValue<string>("imagePath");

    // ---

    texture = TextureHelper::loadTexture(loadResource(texturePath), useMipmap, forceToAlpha);
    
    width = texture->getWidth();
    height = texture->getHeight();
    
    // ---
    
    for (XmlTree::Iter spriteElement = doc.begin("TextureAtlas/sprite"); spriteElement != doc.end(); ++spriteElement)
    {
        string spritePath = spriteElement->getAttributeValue<string>("n");

        float x = spriteElement->getAttributeValue<float>("x");
        float y = spriteElement->getAttributeValue<float>("y");
        float spriteWidth = spriteElement->getAttributeValue<float>("w");
        float spriteHeight = spriteElement->getAttributeValue<float>("h");
        
        float ox = spriteElement->getAttributeValue<float>("oX", 0);
        float oy = spriteElement->getAttributeValue<float>("oY", 0);
        float ow = spriteElement->getAttributeValue<float>("oW", spriteWidth);
        float oh = spriteElement->getAttributeValue<float>("oH", spriteHeight);
        
        bool rotated = spriteElement->hasAttribute("r");
        
        float tx1 = x / width;
        float ty1 = y / height;
        
        float tx2 = (x + spriteWidth) / width;
        float ty2 = (y + spriteHeight) / height;
        
        sprites[spritePath] = new Sprite(spriteWidth, spriteHeight, ox, oy, ow, oh, rotated, tx1, ty1, tx2, ty2);
    }
}

TextureAtlas::~TextureAtlas()
{
    delete texture;
    
    for (map<string, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
    {
        delete it->second;
    }
}

void TextureAtlas::unload()
{
    if (texture)
    {
        delete texture;
        texture = NULL;
    }
}

void TextureAtlas::reload()
{
    if (!texture)
    {
        texture = TextureHelper::loadTexture(loadResource(texturePath));
    }
}

Sprite* TextureAtlas::getSprite(const string &path)
{
    map<string, Sprite*>::iterator it = sprites.find(path);
    
    if (it == sprites.end())
    {
        throw runtime_error("SPRITE NOT FOUND: " + path);
    }

    return it->second;
}

vector<Sprite*> TextureAtlas::getAnimationSprites(const string &path) const
{
    vector<Sprite*> animationSprites;
    string pattern = path + "%d";
    
    for (map<string, Sprite*>::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
    {
        int i = -1;
        sscanf((it->first).c_str(), pattern.c_str(), &i);
        
        if (i != -1)
        {
            animationSprites.push_back(it->second);
        }
    }
    
    return animationSprites;
}

void TextureAtlas::drawSprite(const string &path, float rx, float ry)
{
    sprites[path]->draw(rx, ry);
}

void TextureAtlas::drawSpriteFromCenter(const std::string &path)
{
    sprites[path]->drawFromCenter();
}
