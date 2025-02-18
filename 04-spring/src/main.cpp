#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  auto mainApp = make_shared<ofApp>();

  mainApp->windowWidth = 512;
  mainApp->windowHeight = 512;

  ofGLFWWindowSettings settings;
  settings.setSize(mainApp->windowWidth, mainApp->windowHeight);

  auto anchorWindow = ofCreateWindow(settings);
  auto bobWindow = ofCreateWindow(settings);

  bobWindow->setVerticalSync(false);

  mainApp->anchorWindow = anchorWindow;
  mainApp->bobWindow = bobWindow;

  mainApp->bobWindowSetup();

  ofAddListener(bobWindow->events().update, mainApp.get(),
                &ofApp::bobWindowUpdate);
  ofAddListener(bobWindow->events().mousePressed, mainApp.get(),
                &ofApp::bobWindowMousePressed);
  ofAddListener(bobWindow->events().mouseReleased, mainApp.get(),
                &ofApp::bobWindowMouseReleased);
  ofAddListener(bobWindow->events().draw, mainApp.get(), &ofApp::bobWindowDraw);

  ofRunApp(anchorWindow, mainApp);
  ofRunMainLoop();
}
