/*
 
 layout.h
 
 Layout file is responsible for any utilities used as reference. Later background
   and grid was put in here.
 
 This includes:
  - grid
  - reference images
 */

#pragma once
#include "ofMain.h"

#define _REF_IMAGE "images/ref-img.png"

class Layout {
  
public:
  Layout();
  void drawGrid(int alpha);
  void drawReferenceImage(int alpha);
  void drawBG();
  
  int gridAlpha;
  int gridCount;
  ofImage refImg;
  ofMesh gridMesh;
  
  // BG
  ofImage noiseBG;
private:
  void updateGridAlpha(int alpha);
};