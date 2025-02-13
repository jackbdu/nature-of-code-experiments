#include "Body.h"

void Body::setup() {
  mass = 1;
  radius = 0.1;
  position = ofVec2f{0, 0};
  velocity = ofVec2f{0, 0};
  acceleration = ofVec2f{0, 0};
  bounceFactor = -0.5;
  G = 0.000005;
}

void Body::update() {
  velocity += acceleration;
  position += velocity;
  checkEdges();
  acceleration *= 0;
}

void Body::draw(float refSize) {
  const float r = radius * refSize;
  const float x = ofMap(position.x, 0, 1, r, ofGetWidth() - r);
  const float y = ofMap(position.y, 0, 1, r, ofGetHeight() - r);
  ofDrawCircle(x, y, r);
}

void Body::setMass(float m) { mass = m; }

void Body::setRadius(float r) { radius = r; }

void Body::setPosition(float x, float y) { position = ofVec2f{x, y}; }

void Body::setVelocity(float x, float y) { velocity = ofVec2f{x, y}; }

void Body::setAcceleration(float x, float y) { acceleration = ofVec2f{x, y}; }

void Body::setGravitationalConstant(float g) { G = g; }

void Body::setBounceFactor(float b) { bounceFactor = b; }

ofVec2f Body::attract(Body body, float minDistance, float maxDistance) {
  ofVec2f force = position - body.position;
  const float distance = ofClamp(force.length(), minDistance, maxDistance);
  const float strength = (G * (mass * body.mass)) / (distance * distance);
  force.scale(strength);
  return force;
}

void Body::applyForce(ofVec2f force) {
  const ofVec2f f = force / mass;
  acceleration += f;
}

void Body::checkEdges() {
  if (position.x < 0 || position.x > 1) {
    position.x = ceil(position.x) - position.x;
    velocity.x *= bounceFactor;
  }
  if (position.y < 0 || position.y > 1) {
    position.y = ceil(position.y) - position.y;
    velocity.y *= bounceFactor;
  }
}
