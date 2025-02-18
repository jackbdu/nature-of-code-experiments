#include "Bob.h"

void Bob::setup(float x, float y) {
  position = ofVec2f(x, y);
  velocity = ofVec2f(0, 0);
  acceleration = ofVec2f(0, 0);

  mass = 64;
  radius = sqrt(mass) * 16;
  damping = 0.98;

  dragOffset = ofVec2f(0, 0);
  dragging = false;

  trailLength = 32;
}

void Bob::update() {
  velocity += acceleration;
  velocity *= damping;
  position += velocity;

  acceleration *= 0;

  trail.push_back(position);
  if (trail.size() > trailLength)
    trail.erase(trail.begin());
}

void Bob::applyForce(ofVec2f force) {
  ofVec2f f = force;
  f /= mass;
  acceleration += f;
}

void Bob::show() {
  for (int i = 0; i < trail.size(); ++i) {
    const float progress = float(i) / trail.size();
    const float x = trail[i].x - ofGetWindowPositionX();
    const float y = trail[i].y - ofGetWindowPositionY();
    const float r = radius * sin(HALF_PI * progress);
    ofSetColor(0, ofMap(progress * progress, 0, 1, 0, 255));
    ofDrawCircle(x, y, r);
  }
}

void Bob::handleClick(float mx, float my) {
  dragging = true;
  dragOffset = position - ofVec2f{mx, my};
}

void Bob::handleDrag(float mx, float my) {
  if (dragging)
    position = ofVec2f{mx, my} + dragOffset;
}

void Bob::stopDragging() { dragging = false; }
