#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  for (int i = 0; i < initialSegmentsNum; ++i) {
    const float radius = min(ofGetWidth(), ofGetHeight()) * radiusFactor;
    const float startProgress = float(i) / initialSegmentsNum;
    const float endProgress = float(i + 1) / initialSegmentsNum;
    const float startAngle = startProgress * TWO_PI;
    const float endAngle = endProgress * TWO_PI;
    const float startX = cos(startAngle) * radius;
    const float startY = sin(startAngle) * radius;
    const float endX = cos(endAngle) * radius;
    const float endY = sin(endAngle) * radius;
    ofVec2f start = ofVec2f(startX, startY);
    ofVec2f end = ofVec2f(endX, endY);
    FractalSegment segment;
    segment.setup(start, end);
    segments.push_back(segment);
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  ofBackground(255);

  const float animProgress =
      float(ofGetFrameNum() % animationInterval) / animationInterval;

  fractalize();

  for (int i = 0; i < segments.size(); ++i) {
    segments[i].update(animProgress, bezierControlFactor);
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofSetLineWidth(4);
  ofSetColor(0);
  ofNoFill();
  ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * (0.5 + offsetY));
  ofRotateRad(-HALF_PI);
  for (auto segment : segments) {
    segment.show();
  }
}

//--------------------------------------------------------------
void ofApp::fractalize() {
  FractalSegment segment = segments.front();
  vector<ofVec2f> points = segment.fractalizedPoints();
  for (int i = 0; i <= points.size() - 2; ++i) {
    ofVec2f a = points[i];
    ofVec2f b = points[i + 1];
    FractalSegment segment;
    segment.setup(a, b);
    segments.push_back(segment);
  }
  segments.erase(segments.begin());
}

//--------------------------------------------------------------
void ofApp::exit() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
