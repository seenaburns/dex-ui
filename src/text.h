/*
 
 text.h
 
 Wrapper class for ofTrueTypeFont with more helpful utils
 
 */

#pragma once
#include "ofMain.h"

class Text {
  
public:
  Text();
  
  // Adjusted to draw from top left
  void drawString(string s, float x, float y);
  // Adjusted to draw from top right
  void drawStringFromTopRight(string s, float x, float y);
  
  void setFont(string font, int size);
  ofTrueTypeFont ofFont;
  
private:
};