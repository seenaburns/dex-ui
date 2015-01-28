/*
 
 graph.h
 
 Simple spline graph visualization
 Used for displaying core's performance on left panel
 Has implementation of b-spline from aframes
 
 */

#pragma once
#include "ofMain.h"
#include "text.h"
#include "animated.h"
#include <vector>

class Graph : public Animated {
  
public:
  Graph();
  void update();
  void draw();
  
  void setPos(float x_, float y_);
  void setName(string name_);
  
  float x;
  float y;
  float w;
  float h;
  
  float t;
  
  bool show_rect1;
  bool show_rect2;
  bool show_rect3;
  
  std::vector<ofPoint> aframe_points;
  float new_sample;
  int anchor_count;
  float anchor_xoff;
  float anchor_yoff;
  
  float introLinesDur;
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  vector<AnimatedText> texts;
  
  void bezier_vertex_from_aframe(ofPoint aframe_p1, ofPoint aframe_p2, ofPoint aframe_p3);
  ofPoint intermediate_point(ofPoint p1, ofPoint p2, float distance);
};