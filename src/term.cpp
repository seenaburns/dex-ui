#include "term.h"
#include "graphics-utils.h"
#include "easing-utils.h"
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

Term::Term() {
  setPos(0,0);
  w = 70*GRID_SIZE;
  h = 39*GRID_SIZE;
  inset = 5;
  
  header = Header();
  header.setPos(0,0);
  header.setSize(w);
  header.ul_text = "TERMINAL";
  header.ur_text = "MAIN";
  header.line.duration = 50;
  
  noiseBG.loadImage(NOISE_BG);
  
  t = 0;
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void Term::update() {
  updateTime();
  //  if (currentEvent.id == 0 && getTime() == 200)
  //  system("nohup urxvt >/dev/null 2>&1 &");
  t += 1;
}

void Term::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    if (currentEvent.id == 0) {
      // Intro
      float termDelay = -40;
      
      float outerTermWidth = easeInOut(time+termDelay, 0, w, 30);
      float outerTermHeight = easeInOut(time+termDelay, 0, h, 30);
      float innerTermWidth = easeInOut(time+termDelay, 0, w-inset*2, 40);
      float innerTermHeight = easeInOut(time+termDelay, 0, h-inset*2, 40);
      
      // Background
      ofSetColor(255);
      noiseBG.draw(0.5+inset+(w-inset*2-innerTermWidth)/2,
                   0.5+inset+2*GRID_SIZE+(h-inset*2-innerTermHeight)/2,
                   innerTermWidth,
                   innerTermHeight);
      
      // Outer term
      ofNoFill();
      ofSetColor(COLOR_175, flicker(time+termDelay-10, 10, 3)*255);
      ofRect((w-outerTermWidth)/2,
             0+2*GRID_SIZE+(h-outerTermHeight)/2,
             outerTermWidth,
             outerTermHeight);
      
      // Inner Term
      ofSetColor(COLOR_LINE,flicker(time+termDelay-10, 15, 3)*255);
      ofRect(0.5+inset+(w-inset*2-innerTermWidth)/2,
             0.5+inset+2*GRID_SIZE+(h-inset*2-innerTermHeight)/2,
             innerTermWidth,
             innerTermHeight);
      
      // Header
      float headerAlpha = 0;
      if (time > 60)
        headerAlpha = flicker(time-60, 20, 5)*255;
      header.setAlpha(255,headerAlpha);
      header.draw();
      
    } else if (currentEvent.id == 1) {
      // Main
      // Same as above, without easing
      
      ofNoFill();
      ofSetColor(COLOR_175);
      ofRect(0,2*GRID_SIZE,w,h);
      
      ofSetColor(255,255,255,255);
      noiseBG.draw(0.5+inset,0.5+2*GRID_SIZE+inset,w-inset*2,h-inset*2);
      
      ofSetColor(COLOR_LINE);
      ofRect(0.5+inset,0.5+2*GRID_SIZE+inset,w-inset*2,h-inset*2);
      
      ofSetColor(COLOR_175);
      header.draw();
    }

  }
  ofPopMatrix();
}

void Term::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Term::updateDependencyDelays(int delay_) {
  header.line.setDelay(delay_+0);
}

void Term::updateDependencyEvents() {
  header.line.setEvents(events);
}