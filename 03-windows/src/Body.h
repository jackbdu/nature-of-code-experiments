#ifndef _BODY
#define _BODY

#include "ofMain.h"

class Body {
public:
  void setup();
  void update();
  void draw(float refSize);

  void setMass(float m);
  void setRadius(float r);
  void setPosition(float x, float y);
  void setVelocity(float x, float y);
  void setAcceleration(float x, float y);
  void setGravitationalConstant(float g);
  void setBounceFactor(float b);
  void applyForce(ofVec2f force);
  void checkEdges();
  ofVec2f attract(Body body, float minDistance = 0.025,
                  float maxDistance = 0.25);

  float G;
  float mass;
  float radius;
  float normal;
  float coefficient;
  float bounceFactor;
  ofVec2f position;
  ofVec2f velocity;
  ofVec2f acceleration;
};

#endif
