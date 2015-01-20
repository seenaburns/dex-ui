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
  
  noiseBG.loadImage("images/noise-bg-color-darker.png");
  
  termFont = Text();
  setTextSize(8);
  
  t = 0;
  
  initAnimated();
  newEvent(0, 300, 0, false); // intro
  newEvent(300, -1, 1, false); // main
  header.line.setEvents(events);
}

void Term::update() {
  Animated::update();
  //if (getTime() == 200)
  //  system("nohup urxvt >/dev/null 2>&1 &");
  t += 1;
}

void Term::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    int index = getCurrentEventIndex();
    animation_event_t e = events[index];
    if (e.id == 0) {
      // Intro
      float termDelay = -40;
      
      float outerTermWidth = easeInOut(time+termDelay, 0, w, 30);
      float outerTermHeight = easeInOut(time+termDelay, 0, h, 30);
      float innerTermWidth = easeInOut(time+termDelay, 0, w-inset*2, 40);
      float innerTermHeight = easeInOut(time+termDelay, 0, h-inset*2, 40);
      float headerWidth = easeInOut(time, 0, w, 50);
      
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
      header.setPos((w-headerWidth)/2, 0);
      header.setSize(headerWidth);
      header.setAlpha(255,headerAlpha);
      header.draw();
      
      // Text
      float textdelay = -78;
      ofSetColor(COLOR_175, flicker(time+textdelay, 20, 5)*255);
      //if (time+textdelay > 0)
        //termFont.drawString("nnkd :: ~/ >", inset*4, inset*4 + 2*GRID_SIZE);
    } else if (e.id == 1) {
      // Main
      
      ofNoFill();
      ofSetColor(COLOR_175);
      ofRect(0,2*GRID_SIZE,w,h);
      
      ofSetColor(255,255,255,255);
      noiseBG.draw(0.5+inset,0.5+2*GRID_SIZE+inset,w-inset*2,h-inset*2);
      
      ofSetColor(COLOR_LINE);
      ofRect(0.5+inset,0.5+2*GRID_SIZE+inset,w-inset*2,h-inset*2);
      
      ofSetColor(COLOR_175);
      // termFont.drawString("nnkd :: ~/ >", inset*5, inset*5 + 2*GRID_SIZE);
      
      header.draw();
    }

  }
  ofPopMatrix();
}

void Term::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Term::setTextSize(int size) {
  termFont.setFont(TERMINAL_FONT, size);
}
