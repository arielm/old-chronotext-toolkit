#include "CinderApp.h"
#include "Sketch.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Application : public CinderApp
{
public:
	Application();
	void prepareSettings(Settings *settings);
};

Application::Application()
{
	sketch = new Sketch(this);
}

void Application::prepareSettings(Settings *settings)
{
	settings->setWindowSize(320, 480);
	settings->setFrameRate(60);
}

CINDER_APP_BASIC(Application, RendererGl(0))
