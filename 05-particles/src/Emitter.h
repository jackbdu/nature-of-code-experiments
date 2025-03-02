#pragma once

#include "Particle.h"
#include "ofMain.h"

class Emitter {
public:
  void setup(float x, float y);
  void addParticle();
  void applyForce(ofVec2f force);
  void update();
  void show();

  ofVec2f origin;
  vector<Particle> particles;
};
