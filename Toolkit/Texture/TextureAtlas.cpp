#include "TextureAtlas.h"

#include "cinder/app/AppBasic.h"
#include "cinder/Xml.h"

using namespace ci;
using namespace std;

TextureAtlas::TextureAtlas(DataSourceRef dataSource, bool useMipmap)
{
    XmlTree doc(dataSource);
    
    string resourceName = doc.getChild("TextureAtlas").getAttributeValue<string>("imagePath");
    inputSource = InputSource::getResource(resourceName);

    this->useMipmap = useMipmap;
    
    // ---

    texture = TextureHelper::loadTexture(inputSource, useMipmap);
    
    width = texture->getWidth();
    height = texture->getHeight();
    
    // ---
    
    for (XmlTree::Iter spriteElement = doc.begin("TextureAtlas/sprite"); spriteElement != doc.end(); ++spriteElement)
    {
        string spritePath = spriteElement->getAttributeValue<string>("n");

        float x = spriteElement->getAttributeValue<float>("x");
        float y = spriteElement->getAttributeValue<float>("y");
        float w = spriteElement->getAttributeValue<float>("w");
        float h = spriteElement->getAttributeValue<float>("h");
        
        float ox = spriteElement->getAttributeValue<float>("oX", 0);
        float oy = spriteElement->getAttributeValue<float>("oY", 0);
        float ow = spriteElement->getAttributeValue<float>("oW", w);
        float oh = spriteElement->getAttributeValue<float>("oH", h);
        
        bool rotated = spriteElement->hasAttribute("r");
        
        float tx1 = x / width;
        float ty1 = y / height;
        
        float tx2 = (x + w) / width;
        float ty2 = (y + h) / height;
        
        sprites[spritePath] = new Sprite(texture, w, h, ox, oy, ow, oh, rotated, tx1, ty1, tx2, ty2);
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
        texture = TextureHelper::loadTexture(inputSource, useMipmap);
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

void TextureAtlas::beginTexture()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texture->getId());
}

void TextureAtlas::endTexture()
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void TextureAtlas::drawSprite(const string &path, float rx, float ry)
{
    sprites[path]->draw(rx, ry);
}

void TextureAtlas::drawSpriteFromCenter(const std::string &path)
{
    sprites[path]->drawFromCenter();
}
