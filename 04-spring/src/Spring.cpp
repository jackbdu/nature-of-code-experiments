#include "Spring.h"

void Spring::setup(float x, float y, float width, float length) {
  anchor = ofVec2f(x, y);
  lineWidth = width;
  restLength = length;
  k = 0.2;
}

void Spring::connect(Bob *bob) {
  const ofVec2f direction = bob->position - anchor;
  const float currentLength = direction.length();
  const float stretch = currentLength - restLength;

  const ofVec2f force = direction.getScaled(-1 * k * stretch);

  bob->applyForce(force);
};

void Spring::constrainLength(Bob *bob, float minLen, float maxLen) {
  ofVec2f direction = bob->position - anchor;
  const float length = direction.length();

  if (length < minLen) {
    direction.scale(minLen);
    bob->position = anchor + direction;
    bob->velocity *= 0;
  } else if (length > maxLen) {
    direction.scale(maxLen);
    bob->position = anchor + direction;
    bob->velocity *= 0;
  }
};

void Spring::show() {
  const float anchorX = anchor.x - ofGetWindowPositionX();
  const float anchorY = anchor.y - ofGetWindowPositionY();
  ofSetColor(0);
  ofDrawCircle(anchorX, anchorY, lineWidth);
}

void Spring::showLine(Bob *bob) {
  const float anchorX = anchor.x - ofGetWindowPositionX();
  const float anchorY = anchor.y - ofGetWindowPositionY();
  const float bobX = bob->position.x - ofGetWindowPositionX();
  const float bobY = bob->position.y - ofGetWindowPositionY();
  ofSetLineWidth(lineWidth);
  ofSetColor(0);
  ofDrawLine(bobX, bobY, anchorX, anchorY);
}

void Spring::handleClick(float mx, float my) {
  dragging = true;
  dragOffset = anchor - ofVec2f{mx, my};
}

void Spring::handleDrag(float mx, float my) {
  if (dragging)
    anchor = ofVec2f{mx, my} + dragOffset;
}

void Spring::stopDragging() { dragging = false; }
