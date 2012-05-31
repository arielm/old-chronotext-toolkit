#include "CinderApp.h"

using namespace ci;
using namespace app;
using namespace std;

void CinderApp::setup()
{
	sketch->setup();
	sketch->start(CinderSketch::FLAG_FOCUS_GAIN);
}

void CinderApp::shutdown()
{
    sketch->stop(CinderSketch::FLAG_FOCUS_LOST);
	sketch->shutdown();
	delete sketch;
}

void CinderApp::resize(ResizeEvent event)
{
	sketch->resize(event);
}

void CinderApp::update()
{
	sketch->update();
}

void CinderApp::draw()
{
	sketch->draw();
}

void CinderApp::mouseDown(MouseEvent event)
{
	sketch->addTouch(0, event.getX(), event.getY());
}

void CinderApp::mouseDrag(MouseEvent event)
{
	sketch->updateTouch(0, event.getX(), event.getY());
}

void CinderApp::mouseUp(MouseEvent event)
{
	sketch->removeTouch(0, event.getX(), event.getY());
}
