/*
 
 header.h
 
 The status bar/header that goes on top of left, term, right
 
 */

#pragma once
#include "ofMain.h"
#include "text.h"
#include "animated.h"


class Header {
  
public:
  Header();
  void draw();
  
  void setPos(float x_, float y_);
  void setSize(float w_);
  void setTextSize(int size);
  void setAlpha(float lineAlpha_, float textAlpha_);
  
  float x;
  float y;
  float w;
  float h;
  
  Text font;
  
  string ul_text;
  string ur_text;
  string bl_text;
  string br_text;
  
  ofColor lineC;
  ofColor textC;
  
  float lineAlpha;
  float textAlpha;
  
  AnimatedTickLine line;
};