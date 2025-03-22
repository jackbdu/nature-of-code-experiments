#include "FractalSegment.h"

void FractalSegment::setup(ofVec2f _start, ofVec2f _end) {
  start = _start;
  end = _end;
  controlDirection = (end - start).rotateRad(HALF_PI);
};

void FractalSegment::update(float animProgress, float controlFactor) {
  controlIntensity = cos(animProgress * TWO_PI) * controlFactor;
}

void FractalSegment::show() {
  const ofVec2f controlStart = start + controlDirection * controlIntensity;
  const ofVec2f controlEnd = end + controlDirection * controlIntensity;
  ofDrawBezier(start.x, start.y, controlStart.x, controlStart.y, controlEnd.x,
               controlEnd.y, end.x, end.y);
};

vector<ofVec2f> FractalSegment::fractalizedPoints() {
  ofVec2f a = start;
  ofVec2f e = end;

  ofVec2f c = (start + end) / 2;

  ofVec2f v1 = end - start;
  v1 /= 2;
  ofVec2f v2 = start - end;
  v2 /= 2;
  v1.rotateRad(PI / 3);
  v2.rotateRad(-PI / 3);
  ofVec2f b = a + v1;
  ofVec2f d = e + v2;

  return {a, b, c, d, e};
}
