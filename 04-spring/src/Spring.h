#ifndef _SPRING
#define _SPRING

#include "Bob.h"
#include "ofMain.h"

class Spring {
public:
  void setup(float x, float y, float width, float length);
  void connect(Bob *bob);
  void constrainLength(Bob *bob, float minLen, float maxLen);
  void show();
  void showLine(Bob *bob);
  void handleClick(float mx, float my);
  void handleDrag(float mx, float my);
  void stopDragging();

  ofVec2f anchor;
  float restLength;
  float lineWidth;
  float k;
  ofVec2f dragOffset;
  bool dragging;
};

#endif
