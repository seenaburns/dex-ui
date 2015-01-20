/*
 
 right.h
 
 Right side column of UI utils.
 
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
  void initializeAnimatedItems();
private:
  Header header;
  RadarContainer radar;
  SpikeGraph sg;
  Header footer;
  
  int footer_len;
  float errorDelay;
  
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  vector<AnimatedText> texts;
  
  Text font5;
  
  void initializeTexts();
};