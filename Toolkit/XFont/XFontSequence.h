#pragma once

#include "cinder/gl/gl.h"

struct Slot
{
    int count;
    GLfloat *vertice;
    GLfloat *coords;
    Slot *next;
};

class XFont;

class XFontSequence
{
    XFont *font;
    int dimensions;
    Slot *first, *last, *current;
    int ended;

    void dispose();

public:
    XFontSequence();
    ~XFontSequence();

    void begin(XFont *font, int dimensions);
    void end();
    void flush(GLfloat *vertice, GLfloat *coords, int count);
    void replay();
    void clear();
};
