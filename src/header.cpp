#include "header.h"
#include "graphics-utils.h"

Header::Header() {
  setPos(0,0);
  setSize(0);
  
  font = Text();
  setTextSize(5);
  
  ul_text = "";
  ur_text = "";
  bl_text = "";
  br_text = "";
  
  lineC = COLOR_LINE;
  textC = COLOR_75;
  
  lineAlpha = 255;
  textAlpha = 255;
  
  line.color = lineC;
}

void Header::draw() {
  
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    line.draw();
    ofSetColor(textC, textAlpha);
    font.drawString(ul_text, 5, 6);
    font.drawStringFromTopRight(ur_text, w-5, 6);
    font.drawString(bl_text, 5, h+7);
    font.drawStringFromTopRight(br_text, w-5, h+7);
  }
  ofPopMatrix();
}

void Header::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Header::setSize(float w_) {
  w = w_;
  h = 1*GRID_SIZE;
  line.w = w;
  line.y = h;
}

void Header::setTextSize(int size) {
  font.setFont(MAIN_FONT, size);
}

void Header::setAlpha(float lineAlpha_, float textAlpha_) {
  lineAlpha = lineAlpha_;
  textAlpha = textAlpha_;
  line.alpha = lineAlpha;
}