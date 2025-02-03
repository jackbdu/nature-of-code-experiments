#include "ofApp.h"

const ofColor ofApp::BACKGROUND_COLOR = ofColor(0);
const float ofApp::BRUSH_DETAILS = 1024;
const float ofApp::BRUSH_LENGTH = 1.0;
const float ofApp::BRUSH_RADIUS = 0.05;
const float ofApp::BRUSH_TAIL = 0.1;
const float ofApp::CANVAS_PADDING = 0.2;
const float ofApp::ANIMATION_RATE = 0.01;

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(60);
  ofSetCircleResolution(64);
}

//--------------------------------------------------------------
void ofApp::update() {
  refSize = min(ofGetWidth(), ofGetHeight());
  brushRadius = refSize * BRUSH_RADIUS;
  canvasPadding = refSize * CANVAS_PADDING;
  ofBackground(BACKGROUND_COLOR);
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5, -refSize * 0.5);
  for (float t = 0; t < BRUSH_DETAILS; ++t) {
    const float progress = t / BRUSH_DETAILS;
    const float noiseOffset =
        progress * BRUSH_LENGTH + ofGetFrameNum() * ANIMATION_RATE;
    const float x = ofMap(ofNoise(noiseOffset, 1111), 0, 1,
                          -ofGetWidth() * 0.5 + canvasPadding,
                          ofGetWidth() * 0.5 - canvasPadding);
    const float y = ofMap(ofNoise(noiseOffset, 5555), 0, 1,
                          -ofGetHeight() * 0.5 + canvasPadding,
                          ofGetHeight() * 0.5 - canvasPadding);
    const float z = ofMap(ofNoise(noiseOffset, 9999), 0, 1,
                          -refSize + canvasPadding, refSize - canvasPadding);
    const float lerpAmount =
        ofClamp(ofMap(progress, 0, BRUSH_TAIL, 1, 0), 0, 1);
    ofColor color =
        ofColor(ofMap(sin(progress * TWO_PI / 1 + 0), -1, 1, 0, 255),
                ofMap(sin(progress * TWO_PI / 2 + 0), -1, 1, 0, 255),
                ofMap(sin(progress * TWO_PI / 3 + 0), -1, 1, 0, 255));
    color.lerp(BACKGROUND_COLOR, lerpAmount);
    ofSetColor(color);
    ofDrawCircle(x, y, z, brushRadius);
  }
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
