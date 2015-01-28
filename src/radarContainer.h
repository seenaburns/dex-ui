/*
 
 radarContainer.
 
 Manages positioning of the 3 radars
 
 */

#pragma once
#include "ofMain.h"
#include "radar.h"
#include "text.h"
#include "animated.h"
#include <vector>


class RadarContainer : public Animated {
  
public:
  RadarContainer();
  void draw();
  
  float x;
  float y;
  float w;
  float h;
  ofPoint abs_p;
  
  void setPos(float x_, float y_);
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  Radar radar1;
  Radar radar2;
  Radar radar3;
  
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  vector<AnimatedText> texts;

  void boxIntro();
};