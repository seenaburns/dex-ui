/*
 
 graph.h
 
 Simple spline graph visualization
 
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
  void setDelay(float delay_);
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
  
private:
  Text font5;
  string name;
  
  float delay;
  vector<AnimatedText> texts;
  void initializeText();
  
  void bezier_vertex_from_aframe(ofPoint aframe_p1, ofPoint aframe_p2, ofPoint aframe_p3);
  ofPoint intermediate_point(ofPoint p1, ofPoint p2, float distance);
};