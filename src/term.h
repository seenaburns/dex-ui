/*
 
 term.h
 
 Draws the center terminal frame with the header
 
 */

#pragma once
#include "ofMain.h"
#include "header.h"
#include "text.h"
#include "animated.h"

class Term : public Animated {
  
public:
  Term();
  void update();
  void draw();
  
  float x;
  float y;
  float w;
  float h;
  
  float inset;
  
  float t;
  
  void setPos(float x_, float y_);
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  Header header;
  ofImage noiseBG;
};