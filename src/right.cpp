#include "right.h"
#include "graphics-utils.h"
#include "easing-utils.h"

Right::Right() {
  setPos(0,0);
  w = 240;
 
  header = Header();
  header.setPos(0,0);
  header.setSize(w);
  header.ul_text = "NETWORK";
  header.ur_text = "ALT PANEL";
  header.line.duration = 50;
  header.line.setDelay(0);
  
  radar = RadarContainer();
  radar.setPos(0,2*GRID_SIZE);
  
  sg.setPos(0,32*GRID_SIZE);
  
  footer_len = 6*GRID_SIZE;
  footer = Header();
  footer.setPos(0, 41*GRID_SIZE);
  footer.setSize(footer_len);
  footer.setTextSize(7);
  footer.bl_text = "NNKD";
  footer.line.duration = 50;
  footer.line.setDelay(-90);
  
  font5 = Text();
  font5.setFont(MAIN_FONT, 5);
  
  errorDelay = -80;
  
  initAnimated();
  newEvent(0, 300, 0, false); // intro
  newEvent(300, -1, 1, false); // main
  
  initializeAnimatedItems();
}

void Right::draw() {
  updateTime();
  ofPushMatrix();
  {
    ofTranslate(x, y);
//    ofSetColor(255);
//    ofDrawBitmapString(ofToString(time), 0,-20);

    // Intro
    // Header
    float headerAlpha = 0;
    if (time+header.line.getDelay() > header.line.duration + 10)
      headerAlpha = flicker(time+header.line.getDelay()-(header.line.duration + 10), 20, 5)*255;
    header.setAlpha(255,headerAlpha);
    header.draw();
    
    // Footer
    float footerAlpha = 0;
    if (time+footer.line.getDelay() > footer.line.duration + 10)
      footerAlpha = flicker(time+footer.line.getDelay()-(footer.line.duration + 10), 20, 5)*255;
    footer.setAlpha(255,footerAlpha);
    footer.draw();
//    if (getCurrentEventID() == 0) {
      
      
      radar.draw();
      
      // Error line
      tline1.draw();
      tline2.draw();
      for (int i = 0; i < texts.size(); i++)
        texts[i].draw();
      
      sg.draw();
    /*} else {
      // Main
      radar.draw();
    
      ofSetColor(COLOR_LINE);
      tick_line(0, w, 24*GRID_SIZE);
      tick_line(0, w, 31*GRID_SIZE);
      ofSetColor(COLOR_135);
      font5.drawString("ERROR LOG", 5, 24*GRID_SIZE+7);
      ofSetColor(COLOR_95);
      font5.drawString("NONE", w/2-7, 27*GRID_SIZE+5);
      
      sg.draw();
    }*/
  }
  ofPopMatrix();
}

void Right::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Right::initializeAnimatedItems() {
  header.line.setDelay(delay-0);
  header.line.setEvents(events);
  footer.line.setDelay(delay-90);
  footer.line.setEvents(events);
  radar.setDelay(delay-20);
  radar.setEvents(events);
  tline1 = newTickLine(0, 24*GRID_SIZE, w, 40, delay+errorDelay, COLOR_LINE);
  tline2 = newTickLine(0, 31*GRID_SIZE, w, 40, delay+errorDelay-10, COLOR_LINE);
  tline1.setEvents(events);
  tline2.setEvents(events);
  sg.setDelay(delay-50);
  sg.setEvents(events);
  initializeTexts();
}

void Right::initializeTexts() {
  texts.clear();
  float textDelay = -10;
  // Top Left
  texts.push_back(newText("ERROR LOG", 5,
                          5, 24*GRID_SIZE+7,
                          20, delay+errorDelay-45,
                          COLOR_135,
                          false));
  // Top Right
  texts.push_back(newText("NONE", 5,
                          w/2-7, 27*GRID_SIZE+5,
                          20, delay+errorDelay+textDelay-55,
                          COLOR_95,
                          false));
  
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}