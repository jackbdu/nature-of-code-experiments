#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // CUSTOM PARAMETERS

  particlesNum = 200; // should be consistent with .frag
  wind = ofVec2f(.05, .1);

  shader.load("shadersGL2/shader");

  emitter.setup(ofGetWidth() * 0.5, ofGetHeight() * 0.3);
}

//--------------------------------------------------------------
void ofApp::update() {
  ofBackground(0);

  emitter.addParticle();
  emitter.applyForce(wind);
  emitter.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofVec4f particles[particlesNum];
  fill(particles, particles + particlesNum,
       ofVec4f(emitter.origin.x, emitter.origin.y, 0, 1));

  int particleIndex = 0;

  for (int i = emitter.particles.size() - 1; i >= 0; --i) {
    auto &particle = emitter.particles[i];
    if (particleIndex < particlesNum) {
      particles[particleIndex] =
          ofVec4f(particle.position.x, particle.position.y, particle.lifespan,
                  particle.flickerFreqency);
      ++particleIndex;
    }
  }

  ofLog() << particleIndex << "/" << emitter.particles.size();

  shader.begin();

  shader.setUniform2f("uWindowSize", ofGetWidth(), ofGetHeight());
  shader.setUniform1f("uTime", ofGetElapsedTimef());
  shader.setUniform4fv("uParticles", &particles[0][0], particlesNum);

  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

  shader.end();

  emitter.show();
}

//--------------------------------------------------------------
void ofApp::exit() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) { shader.load("shadersGL2/shader"); }

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) { emitter.origin.set(x, y); }

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) { emitter.origin.set(x, y); }

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
