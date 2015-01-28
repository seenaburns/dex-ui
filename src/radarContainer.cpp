#include "radarContainer.h"
#include "graphics-utils.h"
#include "easing-utils.h"

RadarContainer::RadarContainer() {
  x = 0;
  y = 0;
  w = 240;
  h = 21*GRID_SIZE;
  abs_p = ofPoint(1515, 195);
  
  radar1 = Radar();
  radar1.x = abs_p.x;
  radar1.y = abs_p.y+1*GRID_SIZE;
  radar1.w = w;
  radar1.h = 12*GRID_SIZE;
  radar1.cam.setDistance(375);
  radar1.absolute_center = ofPoint(radar1.x+w/2, radar1.y+(12*GRID_SIZE)/2);
  radar1.set_theta_rate(1/230.0);
  
  radar2 = Radar();
  radar2.x = abs_p.x;
  radar2.y = abs_p.y+14*GRID_SIZE;
  radar2.w = w/2;
  radar2.h = 6*GRID_SIZE;
  radar2.cam.setDistance(425);
  radar2.absolute_center = ofPoint(radar2.x+w/2/2, radar2.y+(6*GRID_SIZE)/2);
  radar2.set_theta_rate(1/150.0);
  
  radar3 = Radar();
  radar3.x = abs_p.x+w/2;
  radar3.y = abs_p.y+14*GRID_SIZE;
  radar3.w = w/2;
  radar3.h = 6*GRID_SIZE;
  radar3.cam.setDistance(425);
  radar3.absolute_center = ofPoint(radar3.x+w/2/2, radar3.y+(6*GRID_SIZE)/2);
  radar3.set_theta_rate(1/130.0);
  
  tline1 = newTickLine(0, 0, w, 40, 0, COLOR_LINE);
  tline2 = newTickLine(0, h, w, 40, 0, COLOR_LINE);
  
  // Top Left
  texts.push_back(newText("MEMORY", 5,
                          5, 7,
                          10, 0,
                          COLOR_135,
                          false));
  // Top Right
  texts.push_back(newText("RADAR VISUALIZATION", 5,
                          w-5, 7,
                          10, 0,
                          COLOR_55,
                          true));
  // Bottom Right
  texts.push_back(newText("SUMMARY", 5,
                          w-4, h-7*GRID_SIZE-11,
                          10, 0,
                          COLOR_55,
                          true));
  // Bottom Left
  texts.push_back(newText("INSPECTION OF", 5,
                          5,h-7*GRID_SIZE-18,
                          10, 0,
                          COLOR_55,
                          false));
  texts.push_back(newText("SYSTEM MEMORY LOAD", 5,
                          5,h-7*GRID_SIZE-11,
                          10, 0,
                          COLOR_55,
                          false));
  // Box Text
  texts.push_back(newText("E1", 5,
                          8, h-1*GRID_SIZE-10,
                          10, 0,
                          COLOR_55,
                          false));
  texts.push_back(newText("E2", 5,
                          8+w/2, h-1*GRID_SIZE-10,
                          10, 0,
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

void RadarContainer::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void RadarContainer::draw() {
  updateTime();
  ofPushMatrix();
  {
    ofTranslate(x, y);

    // Intro
    tline1.draw();
    tline2.draw();
    
    for (int i = 0; i < texts.size(); i++)
      texts[i].draw();
    
    int radar_delay = 75;
    int radar_dur = 50;

    if (currentEvent.id == 0) {
      if (getTime() > radar_delay) {
        if (getTime() < radar_delay+radar_dur) {
          float alpha = easeOut(getTime()-radar_delay, 1, 0, 20);
          float theta = easeOut(getTime()-radar_delay, 0, 2, radar_dur);
          radar1.alphaSub = alpha;
          radar2.alphaSub = alpha;
          radar3.alphaSub = alpha;
          radar1.maxTheta = theta;
          radar2.maxTheta = theta;
          radar3.maxTheta = theta;
          radar1.minTheta = 0;
          radar2.minTheta = 0;
          radar3.minTheta = 0;
        }
        radar1.draw();
        radar2.draw();
        radar3.draw();
      }
    } else {
      radar1.draw();
      radar2.draw();
      radar3.draw();
    }
    
    if (currentEvent.id == 0) {
      boxIntro();
    } else {
      ofNoFill();
      ofSetColor(COLOR_35);
      ofRect(0.5,0.5+h-7*GRID_SIZE,w,6*GRID_SIZE);
      ofRect(0.5+w/2,0.5+h-7*GRID_SIZE,w/2,6*GRID_SIZE);
    }
  }
  ofPopMatrix();
}

void RadarContainer::updateDependencyDelays(int delay_) {
  tline1.setDelay(delay_);
  tline2.setDelay(delay_-10);
  
  int textDelay = -105;
  int textDelays[7] = {0,-5,-10,-15,-15,0,-5};
  for (int i = 0; i < texts.size(); i++)
    texts[i].setDelay(delay_+textDelay+textDelays[i]);
}

void RadarContainer::updateDependencyEvents() {
  tline1.setEvents(events);
  tline2.setEvents(events);
  
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}

void RadarContainer::boxIntro() {
  int boxdelay = -20;
  int boxdurw = 40;
  int boxdurh = 40;
  
  // Boxes
  float boxh = 6*GRID_SIZE;
  float boxy = 0.5+h-7*GRID_SIZE;
  float boxw = w/2;
  float boxx = 0.5;
  float tempBoxw = easeInOut(getTime()+boxdelay, 0, boxw, boxdurw);
  float tempBoxh = easeInOut(getTime()+boxdelay-boxdurw/2, 0, boxh, boxdurh);
  ofNoFill();
  ofSetColor(COLOR_35);
  ofRect(boxx+(w/2-tempBoxw),
         boxy+(boxh-tempBoxh)/2,
         tempBoxw,
         tempBoxh);
  ofRect(boxx+w/2,
         boxy+(boxh-tempBoxh)/2,
         tempBoxw,
         tempBoxh);
}
