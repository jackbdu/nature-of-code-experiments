#include "Particle.h"

void Particle::setup(float x, float y) {
  position = ofVec2f(x, y);
  acceleration = ofVec2f(0, 0);
  velocity = ofVec2f(ofRandom(-3, 3), ofRandom(-3, 0));
  lifespan = 1;
  mass = 1;
  flickerFreqency = ofRandom(3, 8);
}

void Particle::update() {
  velocity += acceleration;
  position += velocity;
  acceleration *= 0;

  lifespan -= 1 / 200.;
}

void Particle::show() {
  ofSetColor(255, 0, 0, lifespan * 255);
  ofDrawCircle(position.x, position.y, 4);
}

void Particle::applyForce(ofVec2f force) {
  force /= mass;
  acceleration += force;
}

bool Particle::isDead() { return lifespan < 0; }
