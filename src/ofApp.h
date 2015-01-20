#pragma once

#include "ofMain.h"
#include "layout.h"
#include "left.h"
#include "right.h"
#include "term.h"
#include "keyboard.h"

#define X_OFFSET 0
#define Y_OFFSET 0

class ofApp : public ofBaseApp{
public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
		
  bool isRecording;
  bool isDrawing;
  int recordFrameCounter;
  int recordMaxFrames;
  
  Layout layout;
  Left left;
  Right right;
  Term term;
  Keyboard keyboard;
};
