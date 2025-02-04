#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  // CUSTOM PARAMETERS

  seed = 0;
  updateIntervalFramesNum = 2;
  offscreenTimeoutFramesNum = 30;
  initialJointRandomness = 0.5;
  pipeRadiusFactor = 0.01;
  jointRadiusFactor = pipeRadiusFactor * 1.5;
  minSegmentLength = 0.08;
  maxSegmentLength = 0.2;
  maxPipesNum = 8;
  minLoopFramesNum = 3600;

  // COLORS

  minHueStep = 30;
  maxHueStep = 90;
  saturation = 100;
  brightness = 255;

  // RENDERING

  ofSetFrameRate(60);
  ofEnableDepthTest();
  ofSetCylinderResolution(32, 1);

  // LIGHTING

  ofEnableLighting();
  directionalLight.setup();
  directionalLight.setDirectional();
  directionalLight.setPosition(ofVec3f{-1, -1, -1});
  directionalLight.lookAt(ofVec3f{0, 0, 0});
  directionalLight.setAmbientColor(ofFloatColor(0.1));
  directionalLight.setDiffuseColor(ofFloatColor(0.9));

  // INITIALIZATIONS

  directions = {0, 1, 2, 3, 4, 5};
  direction = 0;
  offscreenFrameCount = 0;

  ofSetRandomSeed(seed);

  pipes.push_back({ofVec3f{
      ofRandomUniform(-initialJointRandomness, initialJointRandomness),
      ofRandomUniform(-initialJointRandomness, initialJointRandomness),
      ofRandomUniform(-initialJointRandomness, initialJointRandomness)}});

  pipeColors.push_back(
      ofColor::fromHsb(ofRandomUniform(360), saturation, brightness));

  windowResized(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {
  loopProgress = float(ofGetFrameNum()) / minLoopFramesNum;
  if (ofGetFrameNum() % updateIntervalFramesNum == 0) {
    ofVec3f lastJoint = pipes.back().back();
    const ofVec3f lastJointScreenPos = cam.worldToScreen(lastJoint * refSize);
    if (lastJointScreenPos.x < 0 || lastJointScreenPos.x > ofGetWidth() ||
        lastJointScreenPos.y < 0 || lastJointScreenPos.y > ofGetHeight() ||
        lastJoint.z * refSize < pipeBoundZ) {
      ++offscreenFrameCount;
    } else {
      offscreenFrameCount = 0;
    }
    if (offscreenFrameCount > offscreenTimeoutFramesNum) {
      offscreenFrameCount = 0;
      const float hueStep = ofRandomUniform(minHueStep, maxHueStep);
      ofColor color =
          ofColor::fromHsb(int(pipeColors.back().getHue() + hueStep) % 360,
                           saturation, brightness);
      lastJoint = ofVec3f{
          ofRandomUniform(-initialJointRandomness, initialJointRandomness),
          ofRandomUniform(-initialJointRandomness, initialJointRandomness),
          ofRandomUniform(-initialJointRandomness, initialJointRandomness)};
      if (pipes.size() > maxPipesNum) {
        pipes.clear();
        pipeColors.clear();
      }
      pipeColors.push_back(color);
      pipes.push_back({lastJoint});
    }
    const float segmentLength =
        ofRandomUniform(minSegmentLength, maxSegmentLength);
    ofRandomize(directions);
    for (size_t d = 0; d < directions.size(); ++d) {
      // avoid reversing
      if (direction != directions.size() - 1 - directions[d]) {
        direction = directions[d];
        break;
      }
    }
    ofVec3f normalizedSegment;
    // sum of opposite directions equals 5
    switch (direction) {
    case 0:
      normalizedSegment = ofVec3f{1, 0, 0};
      break;
    case 1:
      normalizedSegment = ofVec3f{0, 1, 0};
      break;
    case 2:
      normalizedSegment = ofVec3f{0, 0, 1};
      break;
    case 3:
      normalizedSegment = ofVec3f{0, 0, -1};
      break;
    case 4:
      normalizedSegment = ofVec3f{0, -1, 0};
      break;
    case 5:
      normalizedSegment = ofVec3f{-1, 0, 0};
      break;
    }
    pipes.back().push_back(lastJoint + normalizedSegment * segmentLength);
  }
  ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::draw() {
  cam.begin();
  directionalLight.enable();
  // directionalLight.draw();

  ofRotateYRad(TWO_PI * loopProgress);
  const ofVec3f defaultCylinderOrientation = ofVec3f{0, 1, 0};
  for (size_t p = 0; p < pipes.size(); ++p) {
    ofSetColor(pipeColors[p % pipeColors.size()]);
    auto &joints = pipes[p];
    for (size_t j = 0; j < joints.size(); ++j) {
      auto joint1 = joints[j] * refSize;
      ofPushMatrix();
      ofTranslate(joint1.x, joint1.y, joint1.z);
      if (joints.size() > 1 && (j == 0 || j == joints.size() - 1))
        ofDrawSphere(0, 0, 0, jointRadius);
      if (j + 1 < joints.size()) {
        auto joint2 = joints[j + 1] * refSize;
        ofVec3f segment1 = joint2 - joint1;

        ofPushMatrix();
        ofTranslate(segment1.x / 2, segment1.y / 2, segment1.z / 2);
        const float rotationAngle =
            segment1.angleRad(defaultCylinderOrientation);
        const ofVec3f rotationAxis =
            segment1.getCrossed(defaultCylinderOrientation);
        ofRotateRad(rotationAngle, rotationAxis.x, rotationAxis.y,
                    rotationAxis.z);
        ofDrawCylinder(0, 0, 0, pipeRadius, segment1.length());
        ofPopMatrix();
        ofTranslate(segment1.x, segment1.y, segment1.z);
        if (j + 2 < joints.size()) {
          auto joint3 = joints[j + 2] * refSize;
          ofVec3f segment2 = joint3 - joint2;
          if (segment1.normalize() != segment2.normalize()) {
            ofDrawSphere(0, 0, 0, jointRadius);
          }
        }
      }
      ofPopMatrix();
    }
  }

  directionalLight.disable();
  cam.end();
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
void ofApp::windowResized(int w, int h) {
  refSize = min(ofGetWidth(), ofGetHeight());
  pipeBoundZ = -refSize * 2;
  pipeRadius = pipeRadiusFactor * refSize;
  jointRadius = jointRadiusFactor * refSize;
  cameraDistance = refSize;
  cam.setDistance(cameraDistance);
  cameraFarClipDistance = refSize * 8;
  cam.setFarClip(cameraFarClipDistance);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
