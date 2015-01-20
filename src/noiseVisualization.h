/*
 
 noiseVisualization.h
 
 Noise visualization on bottom left side
 
 */

#pragma once
#include "ofMain.h"
#include "text.h"
#include "waves.h"
#include "animated.h"

class NoiseVisualization : public Animated {
  
public:
  NoiseVisualization();
  void update();
  void draw();
  void drawNoise(bool showHighlights);
  
  void setPos(float x_, float y_);
  void setDelay(float delay_);
  
  float x;
  float y;
  float w;
  float h;
  
  float t;
  float update_x;
  float noise_off;
  float noise_w;
  float noise_h;
  float texw;
  float texh;
  ofShader noiseShader;
  ofImage displacementTexture;
  
  int hi_count;
  std::vector<ofPoint> highlights;
  
private:
  Text font5;
  
  float delay;
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  vector<AnimatedText> texts;
  void initializeText();
  
  void initTexture(int descalar);
  void selectHighlights();
  bool invalidHighlight(int i);
};