#include "Sketch.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

void Sketch::setup(bool renew)
{
    /*
     * UPON DEPLOYMENT ON MSW: PLACE THE FILE IN A resources FOLDER, ALONGSIDE THE EXECUTABLE
     * MORE DETAILS IN chronotext/InputSource.h
     */
    texture = TextureHelper::loadTexture("bulbo1.jpg"); // BULBO IS (C) XEITH FEINBERG, http://www.bulbo.com/
    
    position = getWindowSize() / 2;
    
    // ---

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
}

void Sketch::shutdown()
{
    delete texture;
}

void Sketch::resize(ResizeEvent event)
{
    gl::setMatricesWindow(event.getSize(), true);
}

void Sketch::draw()
{
    glClearColor(1, 0, 0, 1); 
    glClear(GL_COLOR_BUFFER_BIT); 
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ---

    glColor4f(1, 1, 1, 1);
    gl::translate(position);

    TextureHelper::beginTexture(texture);
    TextureHelper::drawTextureFromCenter(texture);
    TextureHelper::endTexture();
}

void Sketch::addTouch(int index, float x, float y)
{
    dragOrigin = Vec2f(x, y) - position;
}

void Sketch::updateTouch(int index, float x, float y)
{
    position = Vec2f(x, y) - dragOrigin;
}
