#include "chronotext/cinder/simple/CinderApp.h"
#include "Sketch.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SimpleSketchApp : public CinderApp
{
public:
    SimpleSketchApp();
    void prepareSettings(Settings *settings);
};

SimpleSketchApp::SimpleSketchApp()
{
    sketch = new Sketch(this);
}

void SimpleSketchApp::prepareSettings(Settings *settings)
{
#if defined(CINDER_MAC) || defined(CINDER_MSW)
    settings->setWindowSize(320, 480);
    settings->setFrameRate(60);
#endif
}

CINDER_APP_NATIVE(SimpleSketchApp, RendererGl)
