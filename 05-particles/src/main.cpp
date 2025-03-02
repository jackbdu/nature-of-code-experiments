/*
 * Based on code example for The Nature of Code (2024 Edition)
 * (https://natureofcode.com/)
 * Ported from p5.js by Jack B. Du
 * (https://github.com/jackbdu/nature-of-code-2024-openframeworks)
 */

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
