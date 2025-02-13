#include "ofApp.h"
#include "GLFW/glfw3.h"

//--------------------------------------------------------------
void ofApp::setup() {

  // CUSTOM PARAMETERS

  gravity = ofVec2f{0, 0};
  bodiesNum = 3;
  bodyMass = 1;
  trailLerpAmount = 0.2;
  bodyPositionInitialRadius = 0.3;
  bodyInitialSpeed = 0.0075;
  enableRandomInitialAngle = false;
  backgroundColor = ofColor(255);
  screenPaddingTop = 0;
  screenPaddingBottom = 0;
  screenPaddingLeft = 0;
  screenPaddingRight = 0;

  // CALCULATED PARAMETERS

  screenAspectRatio = float(ofGetScreenWidth()) / ofGetScreenHeight();

  // RETRIEVE SCREEN AND WINDOW INFO

  auto currentGlfwWindow = glfwGetCurrentContext();

  screenScaleX = 1;
  screenScaleY = 1;
  windowLeft = 0;
  windowTop = 0;
  windowRight = 0;
  windowBottom = 0;
  if (currentGlfwWindow) {
    glfwGetWindowContentScale(currentGlfwWindow, &screenScaleX, &screenScaleY);
    glfwGetWindowFrameSize(currentGlfwWindow, &windowLeft, &windowTop,
                           &windowRight, &windowBottom);
  }
  windowTop *= screenScaleY;
  windowBottom *= screenScaleY;
  windowLeft *= screenScaleX;
  windowRight *= screenScaleX;

  // INITIALIZE ALL BODIES

  for (int i = 0; i < windows.size(); ++i) {
    bodies.push_back(Body());
    bodies.back().setup();
    bodies.back().setPosition(0.5, 0.5);
    bodies.back().setMass(bodyMass);
  }

  // INITIALIZE MAIN BODIES

  for (int i = 0; i < bodiesNum; ++i) {
    const float progress = float(i) / bodiesNum;
    const float angle = progress * TWO_PI;
    const float positionOffsetX = sin(angle) * bodyPositionInitialRadius;
    const float positionOffsetY = cos(angle) * bodyPositionInitialRadius;
    const float velocityAngle =
        enableRandomInitialAngle ? ofRandom(TWO_PI) : angle - HALF_PI;
    const float velocityOffsetX = sin(velocityAngle) * bodyInitialSpeed;
    const float velocityOffsetY = cos(velocityAngle) * bodyInitialSpeed;
    bodies[i].setPosition(0.5 + positionOffsetX, 0.5 + positionOffsetY);
    bodies[i].setVelocity(velocityOffsetX, velocityOffsetY);
  }

  ofSetCircleResolution(64);
}
//--------------------------------------------------------------
void ofApp::setupWindow() { ofSetCircleResolution(64); }

//--------------------------------------------------------------
void ofApp::update() {
  windowRefSize = min(ofGetWidth(), ofGetHeight());
  screenRefSize = min(ofGetScreenWidth(), ofGetScreenHeight());

  // UPDATE TRAILING WINDOWS

  for (int i = windows.size() - 1; i > -1; --i) {
    auto glfwWindow = dynamic_pointer_cast<ofAppGLFWWindow>(windows[i]);
    if (glfwWindow)
      glfwFocusWindow(glfwWindow->getGLFWWindow());

    if (i > bodiesNum - 1) {
      bodies[i].position.interpolate(bodies[i - bodiesNum].position,
                                     trailLerpAmount);
    }
  }

  // APPLY ATTRACTIONS

  for (int i = 0; i < bodiesNum; ++i) {
    for (int j = 0; j < bodiesNum; ++j) {
      if (i != j) {
        const ofVec2f attractionForce = bodies[i].attract(bodies[j]);
        bodies[j].applyForce(attractionForce);
      }
    }
  }

  // APPLY UPDATE ALL BODIES

  for (int i = 0; i < bodiesNum; ++i) {
    bodies[i].applyForce(gravity);
    bodies[i].update();
    ofLog() << i << ": " << bodies[i].position << "; " << bodies[i].velocity;
  }

  // UPDATE MAIN WINDOW

  updateCurrentWindow();
}

//--------------------------------------------------------------
void ofApp::updateWindow(ofEventArgs &args) { updateCurrentWindow(); }

//--------------------------------------------------------------
void ofApp::updateCurrentWindow() {
  int windowIndex;
  for (windowIndex = 0; windowIndex < windows.size(); ++windowIndex) {
    if (windows[windowIndex] == ofGetCurrentWindow())
      break;
  }
  const float minX = windowLeft + screenPaddingLeft;
  const float maxX = ofGetScreenWidth() - ofGetWindowWidth() - windowRight -
                     screenPaddingRight;
  const float minY = windowTop + screenPaddingTop;
  const float maxY = ofGetScreenHeight() - ofGetWindowHeight() - windowRight -
                     screenPaddingBottom;
  const float x = ofMap(bodies[windowIndex].position.x, 0, 1, minX, maxX);
  const float y = ofMap(bodies[windowIndex].position.y, 0, 1, minY, maxY);

  string prefix = ofToString(windowIndex % bodiesNum) + ": ";
  ofSetWindowTitle(prefix + ofToString(ofGetFrameRate(), 2));
  ofSetWindowPosition(x, y);
  ofBackground(backgroundColor);
}

//--------------------------------------------------------------
void ofApp::draw() { drawBodies(); }

//--------------------------------------------------------------
void ofApp::drawWindow(ofEventArgs &args) { drawBodies(); }

//--------------------------------------------------------------
void ofApp::drawBodies() {
  for (int p = 0; p < bodies.size(); ++p) {
    const float progress =
        floor(float(p) / bodiesNum) / (bodies.size() / bodiesNum);
    ofSetColor(0, ofMap(progress, 0, 1, 255, 0));
    bodies[p].draw(windowRefSize);
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
