#include "boxVisualization.h"
#include "graphics-utils.h"
#include "easing-utils.h"

BoxVisualization::BoxVisualization() {
  x = 0;
  y = 0;
  w = 240;
  h = 11*GRID_SIZE;
  setDelay(0);
  
  font5 = Text();
  font5.setFont(MAIN_FONT, 5);

  waves = Waves();
//   waves.setPos(ofPoint(180,270));
//  waves.setPos(ofPoint(75,270));
  waves.setPos(ofPoint(285,375));
  
  initAnimated();
  newEvent(0, 300, 0, true); // intro
  newEvent(0, -1, 1, false); // main
  
  tline1.w = w;
  tline1.duration = 40;
  tline1.setDelay(0);
  
  tline2.y = h;
  tline2.w = w;
  tline2.duration = 40;
  tline2.setDelay(0);
  
  initializeText();
  initializeAnimatedItems();
}

void BoxVisualization::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    int index = getCurrentEventIndex();
    animation_event_t e = events[index];
    // if (e.id == 0) {
      // Intro
      tline1.draw();
      tline2.draw();
      
      if (time + delay > 0) {
        waves.camDist = easeOut(time+delay, 20000, 2400, 50);
        waves.draw();
      }
      
      for (int i = 0; i < texts.size(); i++)
        texts[i].draw();
    /*} else if (e.id == 1) {
      // Main
      ofSetColor(COLOR_LINE);
      // Top
      tick_line(0, w, 0);
      // Bottom
      tick_line(0, w, h);
      
      ofSetColor(COLOR_135);
      font5.drawString("SYSTEM INSPECTOR", 5, 7);
      ofSetColor(COLOR_55);
      font5.drawStringFromTopRight("INVERSION", w-5, 7);
      font5.drawStringFromTopRight("SYSTEM INSPECTOR", w-5, h-11);
      font5.drawStringFromTopRight("LOAD", w-5, h-18);
      ofSetColor(COLOR_55);
      font5.drawStringFromTopRight("HIGH", w-23, h-18);
      
      ofFill();
      ofSetColor(COLOR_55);
      //    ofRect(7, h-27, 2, 23);
      font5.drawString("INITIALIZING ANALYSIS", 5, h-25);
      font5.drawString("OF ADVANCED SYSTEM", 5, h-18);
      font5.drawString("PROCESS INSPECTION", 5, h-11);
      
      
      waves.draw();
    }*/
  }
  ofPopMatrix();
}

void BoxVisualization::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void BoxVisualization::setDelay(float delay_) {
  delay = delay_;
  tline1.setDelay(delay);
  tline2.setDelay(delay-5);
  initializeText();
}

void BoxVisualization::initializeText() {
  texts.clear();
  float textDelay = -55;
  // Top Left
  texts.push_back(newText("SYSTEM SUMMARY", 5,
                          5, 7,
                          10, delay+textDelay,
                          COLOR_135,
                          false));
  // Top Right
  texts.push_back(newText("WAVES VISUALIZATION", 5,
                          w-5, 7,
                          10, delay+textDelay-5,
                          COLOR_55,
                          true));
  // Bottom Right
  texts.push_back(newText("HIGH LOAD", 5,
                          w-5, h-18,
                          10, delay+textDelay-10,
                          COLOR_55,
                          true));
  texts.push_back(newText("ALL ACTIVITY", 5,
                          w-4, h-11,
                          10, delay+textDelay-10,
                          COLOR_55,
                          true));
  // Bottom Left
  texts.push_back(newText("ANALYSIS OF", 5,
                          5,h-18,
                          10, delay+textDelay-15,
                          COLOR_55,
                          false));
  texts.push_back(newText("SYSTEM UTILIZATION", 5,
                          5,h-11,
                          10, delay+textDelay-15,
                          COLOR_55,
                          false));

  initializeAnimatedItems();
}

void BoxVisualization::initializeAnimatedItems() {
  tline1.setEvents(events);
  tline2.setEvents(events);
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}