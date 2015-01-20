#include "left.h"
#include "graphics-utils.h"
#include "easing-utils.h"

Left::Left() {
  x = 0;
  y = 0;
  w = 240;
  delay = 0;
  
  header = Header();
  header.setPos(0,0);
  header.setSize(w);
  header.ul_text = "SYSTEM";
  header.ur_text = "ALT PANEL";
  header.line.duration = 50;
  header.line.setDelay(0);
  
  
  timeDisplay = TimeDisplay();
  timeDisplay.setPos(0,2*GRID_SIZE);
  timeDisplay.setDelay(-20);
  
  boxVis = BoxVisualization();
  boxVis.setPos(0, 9*GRID_SIZE);
  boxVis.setDelay(-25);
  
  g1 = Graph();
  g2 = Graph();
  g3 = Graph();
  g4 = Graph();
  int graph_start=21;
  g1.setPos(0, (graph_start)*GRID_SIZE);
  g2.setPos(0, (graph_start+3)*GRID_SIZE);
  g3.setPos(0, (graph_start+6)*GRID_SIZE);
  g4.setPos(0, (graph_start+9)*GRID_SIZE);
  g1.setDelay(ofRandom(25)-60);
  g2.setDelay(ofRandom(25)-60);
  g3.setDelay(ofRandom(25)-60);
  g4.setDelay(ofRandom(25)-60);
  g1.setName("CORE L1");
  g2.setName("CORE L2");
  g3.setName("CORE L3");
  g4.setName("CORE L4");
  
  noiseVis = NoiseVisualization();
  noiseVis.setPos(0, 33*GRID_SIZE);
  noiseVis.setDelay(-40);
  
  footer_len = 6*GRID_SIZE;
  footer = Header();
  footer.setPos(w-footer_len, 41*GRID_SIZE);
  footer.setSize(footer_len);
  footer.setTextSize(7);
  footer.br_text = "DEX UI";
  footer.line.duration = 50;
  footer.line.setDelay(-90);
  
  initAnimated();
  newEvent(0, 300, 0, false); // intro
  newEvent(0, -1, 1, false); // main
  initializeAnimatedItems();
}

void Left::update() {
  Animated::update();
}

void Left::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
//    ofSetColor(255);
//    ofDrawBitmapString(ofToString(time), 0,-20);
    
    int index = getCurrentEventIndex();
    animation_event_t e = events[index];
    if (e.id == 0) {
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
      
      // Time Display
      timeDisplay.draw();
      
      boxVis.draw();
      
      g1.draw();
      g2.draw();
      g3.draw();
      g4.draw();
      
      noiseVis.draw();
      
    } else if (e.id == 1) {
      // Main
      header.draw();
      timeDisplay.draw();
      boxVis.draw();
      //    ofSetColor(255,255,255);
      //    tick_line(0, w, 0);
      
      g1.draw();
      g2.draw();
      g3.draw();
      g4.draw();
      
      noiseVis.draw();
      
      footer.draw();
    }
  }
  ofPopMatrix();
}

void Left::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Left::setDelay(float delay_) {
  delay = delay_;
  header.line.setDelay(delay);
  timeDisplay.setDelay(delay-20);
  boxVis.setDelay(delay-25);
  g1.setDelay(delay-ofRandom(25)-60);
  g2.setDelay(delay-ofRandom(25)-60);
  g3.setDelay(delay-ofRandom(25)-60);
  g4.setDelay(delay-ofRandom(25)-60);
  noiseVis.setDelay(delay-40);
  footer.line.setDelay(delay-90);
}

void Left::initializeAnimatedItems() {
  header.line.setEvents(events);
  footer.line.setEvents(events);
  timeDisplay.setEvents(events);
  boxVis.setEvents(events);
  g1.setEvents(events);
  g2.setEvents(events);
  g3.setEvents(events);
  g4.setEvents(events);
  noiseVis.setEvents(events);
}