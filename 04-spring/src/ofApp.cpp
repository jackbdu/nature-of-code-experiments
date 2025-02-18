#include "ofApp.h"
#include "GLFW/glfw3.h"

//--------------------------------------------------------------
void ofApp::setup() {

  // CUSTOM PARAMETERS

  gravity = ofVec2f{0, 128};
  backgroundColor = ofColor(255);

  springWidth = 16;
  springLength = ofGetScreenHeight() * 0.3;

  // INITIALIZE SPRING

  spring.setup(ofGetScreenWidth() * 0.5, 0, springWidth, springLength);
  bob.setup(ofGetScreenWidth() * 0.5, springLength);

  ofSetWindowTitle("Anchor");
  ofSetCircleResolution(64);
}

//--------------------------------------------------------------
void ofApp::bobWindowSetup() {
  ofSetWindowTitle("Bob");
  ofSetCircleResolution(64);
}

//--------------------------------------------------------------
void ofApp::update() {
  auto currentGlfwWindow = glfwGetCurrentContext();
  if (currentGlfwWindow) {
    double mouseScreenX;
    double mouseScreenY;
    float mouseScaleX;
    float mouseScaleY;
    glfwGetCursorPos(currentGlfwWindow, &mouseScreenX, &mouseScreenY);
    glfwGetWindowContentScale(currentGlfwWindow, &mouseScaleX, &mouseScaleY);

    mouseScreenCoord.x = mouseScreenX * mouseScaleX + ofGetWindowPositionX();
    mouseScreenCoord.y = mouseScreenY * mouseScaleY + ofGetWindowPositionY();
  }

  spring.handleDrag(mouseScreenCoord.x, mouseScreenCoord.y);
  spring.connect(&bob);
  spring.constrainLength(&bob, 0, ofGetScreenHeight());

  // UPDATE MAIN WINDOW

  ofSetWindowPosition(spring.anchor.x - ofGetWidth() * 0.5, spring.anchor.y);

  ofLog() << "Anchor: " << spring.anchor << "; Bob: " << bob.position
          << "; Mouse: " << mouseScreenCoord;

  ofBackground(backgroundColor);
}

//--------------------------------------------------------------
void ofApp::bobWindowUpdate(ofEventArgs &args) {
  const float x = bob.position.x;
  const float y = bob.position.y;

  bob.applyForce(gravity);
  bob.handleDrag(mouseScreenCoord.x, mouseScreenCoord.y);
  bob.update();

  ofSetWindowPosition(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.5);

  ofBackground(backgroundColor);
}

//--------------------------------------------------------------
void ofApp::draw() {
  spring.showLine(&bob);
  spring.show();
  bob.show();
}

//--------------------------------------------------------------
void ofApp::bobWindowDraw(ofEventArgs &args) { draw(); }

//--------------------------------------------------------------
void ofApp::bobWindowMousePressed(ofMouseEventArgs &args) {
  bob.handleClick(mouseScreenCoord.x, mouseScreenCoord.y);
}

//--------------------------------------------------------------
void ofApp::bobWindowMouseReleased(ofMouseEventArgs &args) {
  bob.stopDragging();
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
void ofApp::mousePressed(int x, int y, int button) {
  spring.handleClick(mouseScreenCoord.x, mouseScreenCoord.y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) { spring.stopDragging(); }

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
