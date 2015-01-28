/*
 
 boxVisualization.h
 
 Box/Waves visualization, in the style of Tron boardroom
 Is dependent on absolute positioning because of waves
 
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
  
  float x;
  float y;
  float w;
  float h;
  
  Waves waves;
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  vector<AnimatedText> texts;
};