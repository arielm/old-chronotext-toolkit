#include "FlashShape.h"

using namespace ci;
using namespace std;

void FlashShape::appendVertices(const Vec2f *vertices, size_t num)
{
    this->vertices.insert(this->vertices.end(), vertices, vertices + num);
}

void FlashShape::appendIndices(uint32_t *indices, size_t num)
{
    this->indices.reserve(this->indices.size() + num);
    
    for (int i = 0; i < num; i++)
    {
        this->indices.push_back((uint16_t)indices[i]);
    }
}

void FlashShape::draw(Texture *strokeTexture)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    
    strokeTexture->bind();
    strip.draw();
    
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
