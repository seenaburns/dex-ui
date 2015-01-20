/*
 
 layout.h
 
 Layout file is responsible for any utilities used as reference.
 This includes:
  - grid
  - column hints
  - reference images
 
 */

#pragma once
#include "ofMain.h"

#define _REF_IMAGE "images/ref-img.png"

class Layout {
  
public:
  Layout();
  void drawGrid(int alpha);
  void drawColumns(int alpha);
  void drawReferenceImage(int alpha);
  void drawBG();
  void drawScannerlines();
  
  int gridAlpha;
  int gridCount;
  ofImage refImg;
  ofMesh gridMesh;
  
  // BG
  ofImage noiseBG;
  
  // Scannerlines
  ofShader scannerShader;
  
private:
  void updateGridAlpha(int alpha);
};