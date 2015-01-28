#include "boxVisualization.h"
#include "graphics-utils.h"
#include "easing-utils.h"

BoxVisualization::BoxVisualization() {
  x = 0;
  y = 0;
  w = 240;
  h = 11*GRID_SIZE;
  setDelay(0);

  waves = Waves();
  waves.setPos(ofPoint(285,375));
  
  tline1.w = w;
  tline1.duration = 40;
  tline1.setDelay(0);
  
  tline2.y = h;
  tline2.w = w;
  tline2.duration = 40;
  tline2.setDelay(0);
  
  texts.clear();
  int textDelay = -55;
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
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void BoxVisualization::draw() {
  updateTime();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    // Intro
    tline1.draw();
    tline2.draw();
    
    if (currentEvent.id == 0 && getTime() > 0)
      waves.camDist = easeOut(getTime(), 20000, 2400, 50);
    if (getTime() > 0)
      waves.draw();
    
    for (int i = 0; i < texts.size(); i++)
      texts[i].draw();
}
  ofPopMatrix();
}

void BoxVisualization::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void BoxVisualization::updateDependencyDelays(int delay_) {
  delay = delay_;
  tline1.setDelay(delay);
  tline2.setDelay(delay-5);
  
  int textDelay = -55;
  int textDelays[6] = {0,-5,-10,-10,-15,-15};
  for (int i = 0; i < texts.size(); i++)
    texts[i].setDelay(delay_+textDelay+textDelays[i]);
}

void BoxVisualization::updateDependencyEvents() {
  tline1.setEvents(events);
  tline2.setEvents(events);
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}
