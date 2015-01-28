/*
 
 right.h
 
 Right panel of UI utils.
 
 */

#pragma once
#include "ofMain.h"
#include "header.h"
#include "radarContainer.h"
#include "spikeGraph.h"
#include "animated.h"


class Right : public Animated {
public:
  Right();
  void draw();
  
  float x;
  float y;
  float w;
  float h;
  
  void setPos(float x_, float y_);
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  vector<AnimatedText> texts;
  Header header;
  RadarContainer radar;
  SpikeGraph sg;
  Header footer;
  
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
};