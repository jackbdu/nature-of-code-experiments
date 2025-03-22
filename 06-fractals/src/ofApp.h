#pragma once

#include "FractalSegment.h"
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

  void fractalize();

  vector<FractalSegment> segments;
  const int initialSegmentsNum = 3;
  const int animationInterval = 300;
  const float radiusFactor = 0.1;
  const float bezierControlFactor = 0.0;
  const float offsetY = radiusFactor * cos(PI / 3) * tan(PI / 3) / 8;
};
