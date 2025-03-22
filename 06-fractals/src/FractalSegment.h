#pragma once

#include "ofMain.h"

class FractalSegment {
public:
  void setup(ofVec2f _start, ofVec2f _end);
  void show();
  void update(float animProgress, float controlFactor);
  vector<ofVec2f> fractalizedPoints();

  ofVec2f start;
  ofVec2f end;
  ofVec2f controlDirection;
  float controlIntensity;
};
