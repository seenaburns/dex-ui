/*
 
 noiseVisualization.h
 
 Noise visualization on bottom left panel
 Dots are generated from 2D Perlin noise
 
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
  void drawNoise();
  
  void setPos(float x_, float y_);
  
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

  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  vector<AnimatedText> texts;
  
  void initTexture(int descalar);
};