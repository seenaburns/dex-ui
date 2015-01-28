#include "left.h"
#include "graphics-utils.h"
#include "easing-utils.h"

Left::Left() {
  // Default position vars
  x = 0;
  y = 0;
  w = 240;
  delay = 0;
  
  header.setPos(0,0);
  header.setSize(w);
  header.ul_text = "SYSTEM";
  header.ur_text = "ALT PANEL";
  header.line.duration = 50;
  
  timeDisplay.setPos(0,2*GRID_SIZE);
  
  boxVis.setPos(0, 9*GRID_SIZE);
  
  int graph_start=21;
  g1.setPos(0, (graph_start)*GRID_SIZE);
  g2.setPos(0, (graph_start+3)*GRID_SIZE);
  g3.setPos(0, (graph_start+6)*GRID_SIZE);
  g4.setPos(0, (graph_start+9)*GRID_SIZE);
  g1.setName("CORE L1");
  g2.setName("CORE L2");
  g3.setName("CORE L3");
  g4.setName("CORE L4");
  
  noiseVis.setPos(0, 33*GRID_SIZE);
  
  footer_len = 6*GRID_SIZE;
  footer.setPos(w-footer_len, 41*GRID_SIZE);
  footer.setSize(footer_len);
  footer.setTextSize(7);
  footer.br_text = "DEX UI";
  footer.line.duration = 50;
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void Left::draw() {
  updateTime();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    if (currentEvent.id == 0) {
      // Intro
      // Set header / footer colors
      
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
    timeDisplay.draw();
    boxVis.draw();
    g1.draw();
    g2.draw();
    g3.draw();
    g4.draw();
    noiseVis.draw();
    footer.draw();
  }
  ofPopMatrix();
}

void Left::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Left::updateDependencyDelays(int delay_) {
  header.line.setDelay(delay_+0);
  timeDisplay.setDelay(delay_+-20);
  boxVis.setDelay(delay_+-25);
  g1.setDelay(delay_+ofRandom(25)-60);
  g2.setDelay(delay_+ofRandom(25)-60);
  g3.setDelay(delay_+ofRandom(25)-60);
  g4.setDelay(delay_+ofRandom(25)-60);
  noiseVis.setDelay(delay_+-40);
  footer.line.setDelay(delay_+-90);
}

void Left::updateDependencyEvents() {
  header.line.setEvents(events);
  timeDisplay.setEvents(events);
  boxVis.setEvents(events);
  g1.setEvents(events);
  g2.setEvents(events);
  g3.setEvents(events);
  g4.setEvents(events);
  noiseVis.setEvents(events);
  footer.line.setEvents(events);
}