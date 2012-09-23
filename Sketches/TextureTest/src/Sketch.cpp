#include "Sketch.h"
#include "Resources.h"

using namespace std;
using namespace ci;
using namespace ci::app;

void Sketch::setup()
{
    texture1 = textureManager.getTexture(InputSource::getResource("hatch.png"), true, TextureHelper::FILTER_TRANSLUCENT);
    texture2 = textureManager.getTexture(InputSource::getResource(RES_B));
    texture3 = textureManager.getTexture(InputSource::getFileInDocuments("Atlas-2_IPAD1.pvr.gz")); // XXX: BE SURE TO HAVE SUCH A FILE IN THE DOCUMENTS FOLDER
    
    // ---
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
}

void Sketch::shutdown()
{
}

void Sketch::resize(ResizeEvent event)
{
    gl::setMatricesWindow(event.getSize(), true);
}

void Sketch::draw()
{
    glClearColor(1, 0.75, 0.25, 1); 
    glClear(GL_COLOR_BUFFER_BIT); 
	
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // ---
    
    glColor4f(1, 1, 1, 1);
    gl::translate(getWindowSize() / 2);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    
    texture3->bind();
    texture3->drawFromCenter();
    
    texture2->bind();
    texture2->drawFromCenter();
    
    texture1->bind();
    texture1->drawFromCenter();
    
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
