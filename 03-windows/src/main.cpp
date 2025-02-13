#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  auto mainApp = make_shared<ofApp>();

  mainApp->windowWidth = 512;
  mainApp->windowHeight = 512;
  mainApp->windowsNum = 15;

  ofGLFWWindowSettings settings;
  settings.setSize(mainApp->windowWidth, mainApp->windowHeight);
  settings.resizable = false;

  auto mainWindow = ofCreateWindow(settings);

  mainApp->windows.push_back(mainWindow);
  for (int i = 0; i < mainApp->windowsNum - 1; ++i) {
    auto window = ofCreateWindow(settings);
    window->setVerticalSync(false);

    mainApp->setupWindow();
    mainApp->windows.push_back(window);
    ofAddListener(window->events().update, mainApp.get(), &ofApp::updateWindow);
    ofAddListener(window->events().draw, mainApp.get(), &ofApp::drawWindow);
  }

  ofRunApp(mainWindow, mainApp);
  ofRunMainLoop();
}
