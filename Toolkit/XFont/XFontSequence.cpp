#include "XFontSequence.h"
#include "XFont.h"

XFontSequence::XFontSequence()
{
    first = last = current = NULL;
    ended = 0;
}

XFontSequence::~XFontSequence()
{
    dispose();
}

void XFontSequence::dispose()
{
    Slot *tmp;
    current = first;
    while (current)
    {
        tmp = current;
        current = current->next;
        
        free(tmp->vertice);
        free(tmp->coords);
        free(tmp);
    }
}

void XFontSequence::begin(XFont *font, int dimensions)
{
    if (!ended)
    {
        this->font = font;
        this->dimensions = dimensions;
    }
    else
    {
        current = first;
    }
}

void XFontSequence::end()
{
    ended++;
}

void XFontSequence::flush(GLfloat *vertice, GLfloat *coords, int count)
{
    if (!ended)
    {
        current = (Slot *) calloc(1, sizeof(Slot)); // USING malloc WOULD REQUIRE: current->next = NULL
        current->count = count;
		
        int verticeCapacity = count * dimensions * 4;
        current->vertice = (GLfloat *) malloc(verticeCapacity * sizeof(GLfloat));
        memcpy(current->vertice, vertice, verticeCapacity * sizeof(GLfloat));
		
        int coordsCapacity = count * 2 * 4;
        current->coords = (GLfloat *) malloc(coordsCapacity * sizeof(GLfloat));
        memcpy(current->coords, coords, coordsCapacity * sizeof(GLfloat));
        
        if (last)
        {
            last->next = current;
        }
        else
        {
            first = current;
        }
        last = current;
    }
    else
    {
        memcpy(current->vertice, vertice, count * dimensions * 4 * sizeof(GLfloat));
        current = current->next;
    }
}

void XFontSequence::replay()
{
    font->begin();
    
    current = first;
    while (current)
    {
        glVertexPointer(dimensions, GL_FLOAT, 0, current->vertice);
        glTexCoordPointer(2, GL_FLOAT, 0, current->coords);
        glDrawElements(GL_TRIANGLES, current->count * 6, GL_UNSIGNED_SHORT, font->getIndices());
		
        current = current->next;
    }
    
    font->end();
}

void XFontSequence::clear()
{
    dispose();
    first = last = current = NULL;
    ended = 0;
}
