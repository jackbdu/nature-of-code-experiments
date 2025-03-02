#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {

  ofGLWindowSettings settings;
  settings.setSize(1920, 1080);
  settings.windowMode = OF_WINDOW;

  auto window = ofCreateWindow(settings);

  ofRunApp(window, make_shared<ofApp>());
  ofRunMainLoop();
}
