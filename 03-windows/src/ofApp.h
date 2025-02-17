#pragma once

#include "Body.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
  void setup() override;
  void update() override;
  void draw() override;
  void exit() override;

  void keyPressed(int key) override;
  void keyReleased(int key) override;
  void mouseMoved(int x, int y) override;
  void mouseDragged(int x, int y, int button) override;
  void mousePressed(int x, int y, int button) override;
  void mouseReleased(int x, int y, int button) override;
  void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
  void mouseEntered(int x, int y) override;
  void mouseExited(int x, int y) override;
  void windowResized(int w, int h) override;
  void dragEvent(ofDragInfo dragInfo) override;
  void gotMessage(ofMessage msg) override;

  // ADDITIONAL EVENTS

  void setupWindow();
  void updateWindow(ofEventArgs &args);
  void drawWindow(ofEventArgs &args);

  // SHARED FUNCTIONS

  void updateCurrentWindow();
  void drawBodies();

  // MAIN.CPP

  vector<shared_ptr<ofAppBaseWindow>> windows;
  int windowWidth;
  int windowHeight;
  int windowsNum;

  // OFAPP.CPP

  int bodiesNum;
  int windowTop;
  int windowBottom;
  int windowLeft;
  int windowRight;
  int screenPaddingTop;
  int screenPaddingBottom;
  int screenPaddingLeft;
  int screenPaddingRight;
  float screenScaleX;
  float screenScaleY;
  float windowRefSize;
  float screenRefSize;
  float screenAspectRatio;
  float trailLerpAmount;
  float bodyMass;
  float bodyPositionInitialRadius;
  float bodyInitialSpeed;
  bool enableRandomInitialAngle;
  ofColor backgroundColor;
  vector<Body> bodies;
  ofVec2f gravity;
};
