#include "layout.h"
#include "graphics-utils.h"

Layout::Layout() {
  // Create grid mesh
  // Use mesh over series of rectangles for performance
  gridAlpha = 255;
  gridCount = 0;
  gridMesh.setMode(OF_PRIMITIVE_POINTS);
  for (int x = 0; x < WIDTH; x+=GRID_SIZE){
    for (int y = 0; y < HEIGHT; y+=GRID_SIZE){
      // Offset by 0.5 to ensure 1px points
      gridMesh.addVertex(ofPoint(x+0.5,y+0.5,0));
      gridMesh.addColor(ofColor(255,255,255,gridAlpha));
      gridMesh.addIndex(gridCount);
      gridCount += 1;
    }
  }
  
  refImg.loadImage(_REF_IMAGE);
  noiseBG.loadImage(NOISE_BG);
}

void Layout::drawGrid(int alpha) {
  if (alpha != gridAlpha)
    updateGridAlpha(alpha);
  gridMesh.draw();
}

void Layout::drawReferenceImage(int alpha) {
  ofSetColor(255,255,255,alpha);
  refImg.draw(0,0);
}

void Layout::drawBG() {
  ofSetColor(255,255,255,255);
  noiseBG.draw(0,0);
}

void Layout::updateGridAlpha(int alpha) {
  gridAlpha = alpha;
  gridMesh.setColorForIndices(0, gridCount, ofColor(255,255,255,gridAlpha));
}