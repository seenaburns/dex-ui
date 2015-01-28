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
  
  radar = RadarContainer();
  radar.setPos(0,2*GRID_SIZE);
  
  sg.setPos(0,32*GRID_SIZE);
  
  footer = Header();
  footer.setPos(0, 41*GRID_SIZE);
  footer.setSize(6*GRID_SIZE);
  footer.setTextSize(7);
  footer.bl_text = "NNKD";
  footer.line.duration = 50;

  // Error section
  tline1 = newTickLine(0, 24*GRID_SIZE, w, 40, 0, COLOR_LINE);
  tline2 = newTickLine(0, 31*GRID_SIZE, w, 40, 0, COLOR_LINE);
  texts.push_back(newText("ERROR LOG", 5,
                          5, 24*GRID_SIZE+7,
                          20, 0,
                          COLOR_135,
                          false));
  texts.push_back(newText("NONE", 5,
                          w/2-7, 27*GRID_SIZE+5,
                          20, 0,
                          COLOR_95,
                          false));
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void Right::draw() {
  updateTime();
  ofPushMatrix();
  {
    ofTranslate(x, y);

    if (currentEvent.id == 0) {
      // Intro
      // Header
      float headerAlpha = 0;
      if (time+header.line.getDelay() > header.line.duration + 10)
        headerAlpha = flicker(time+header.line.getDelay()-(header.line.duration + 10), 20, 5)*255;
      header.setAlpha(255,headerAlpha);
      
      // Footer
      float footerAlpha = 0;
      if (time+footer.line.getDelay() > footer.line.duration + 10)
        footerAlpha = flicker(time+footer.line.getDelay()-(footer.line.duration + 10), 20, 5)*255;
      footer.setAlpha(255,footerAlpha);
    }
    header.draw();
    footer.draw();
    
    // Radar
    radar.draw();
    
    // Error section
    tline1.draw();
    tline2.draw();
    for (int i = 0; i < texts.size(); i++)
      texts[i].draw();
    
    // Spike Graph
    sg.draw();
  }
  ofPopMatrix();
}

void Right::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Right::updateDependencyDelays(int delay_) {
  header.line.setDelay(delay_);
  tline1.setDelay(delay_-80);
  tline2.setDelay(delay_-90);
  sg.setDelay(delay_-50);
  radar.setDelay(delay_-20);
  footer.line.setDelay(delay_-90);
  
  int textDelay = -90;
  int textDelays[2] = {-45,-55};
  for (int i = 0; i < texts.size(); i++)
    texts[i].setDelay(delay_+textDelay+textDelays[i]);
}

void Right::updateDependencyEvents() {
  header.line.setEvents(events);
  tline1.setEvents(events);
  tline2.setEvents(events);
  sg.setEvents(events);
  radar.setEvents(events);
  footer.line.setEvents(events);
  
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}
