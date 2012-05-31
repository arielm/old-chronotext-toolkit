#pragma once

#include "cinder/gl/gl.h"

typedef struct Slot
{
	int count;
	GLfloat *vertice;
	GLfloat *coords;
	struct Slot *next;
} Slot;

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
