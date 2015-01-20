/*
 
 boxVisualization.h
 
 Box visualization in the style of tron, on left side below time display
 
 */

#pragma once
#include "ofMain.h"
#include "text.h"
#include "waves.h"
#include "animated.h"
#include <vector>

class BoxVisualization : public Animated {
  
public:
  BoxVisualization();
  void draw();
  
  void setPos(float x_, float y_);
  void setDelay(float delay_);
  
  float x;
  float y;
  float w;
  float h;
  
  Waves waves;
  void initializeAnimatedItems();
private:
  Text font5;
  
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  vector<AnimatedText> texts;
  float delay;
  
  void initializeText();
};