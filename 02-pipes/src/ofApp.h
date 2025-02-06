#pragma once

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

  ofEasyCam cam;
  ofLight directionalLight;
  vector<vector<ofVec3f>> pipes;
  vector<ofColor> pipeColors;
  vector<int> directions;
  ofVec3f pdirection;
  ofVec3f direction;
  float refSize;
  float pipeRadiusFactor;
  float jointRadiusFactor;
  float pipeRadius;
  float jointRadius;
  float cameraDistance;
  float cameraFarClipDistance;
  float pipeBoundZ;
  float minSegmentLength;
  float maxSegmentLength;
  float minHueStep;
  float maxHueStep;
  float saturation;
  float brightness;
  float initialJointRandomness;
  float loopProgress;
  int minLoopFramesNum;
  int updateIntervalFramesNum;
  int offscreenTimeoutFramesNum;
  int offscreenFrameCount;
  int maxPipesNum;
  int seed;
};
