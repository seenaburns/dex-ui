/*
 
 left.h
 
 Left panel of UI utils.
 Manages timeDisplay, boxVisualization, graphs, and two header objects.
 
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
  void draw();
  void setPos(float x_, float y_);
  
  float x;
  float y;
  float w;
  float h;
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
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
};