#include "TextureAtlas.h"

#include "cinder/app/AppBasic.h"
#include "cinder/DataSource.h"
#include "cinder/Xml.h"

using namespace ci;
using namespace ci::app;
using namespace std;

TextureAtlas::TextureAtlas(DataSourceRef dataSource)
{
    XmlTree doc(dataSource);
    
    const XmlTree textureAtlasElement = doc.getChild("TextureAtlas");
    texturePath = textureAtlasElement.getAttributeValue<string>("imagePath");

    // ---

    texture = TextureHelper::loadTexture(loadResource(texturePath));
    
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
        
        sprites[spritePath] = Sprite(spriteWidth, spriteHeight, ox, oy, ow, oh, rotated, tx1, ty1, tx2, ty2);
    }
}

TextureAtlas::~TextureAtlas()
{
    delete texture;
}

void TextureAtlas::clear()
{
    if (texture)
    {
        delete texture;
        texture = NULL;
    }
}

void TextureAtlas::reload()
{
    clear();
    texture = TextureHelper::loadTexture(loadResource(texturePath));
}

Sprite TextureAtlas::getSprite(const string &path)
{
    return sprites[path];
}

void TextureAtlas::drawSprite(const string &path, float rx, float ry, bool originUp)
{
    sprites[path].draw(rx, ry, originUp);
}
