/*
 
 left.h
 
 Left side column of UI utils.
 This class is a wrapper for the individual elements, and makes them act as a 
 single unit.
 
 */

#pragma once
#include "ofMain.h"
#include "header.h"
#include "timeDisplay.h"
#include "boxVisualization.h"
#include "graph.h"
#include "noiseVisualization.h"
#include "animated.h"


class Left : public Animated {
  
public:
  Left();
  void update();
  void draw();
  void setPos(float x_, float y_);
  void setDelay(float delay_);
  
  float x;
  float y;
  float w;
  float h;
  
  void initializeAnimatedItems();
private:
  Header header;
  TimeDisplay timeDisplay;
  BoxVisualization boxVis;
  Graph g1;
  Graph g2;
  Graph g3;
  Graph g4;
  NoiseVisualization noiseVis;
  Header footer;
  
  float footer_len;
  
  float delay;
};