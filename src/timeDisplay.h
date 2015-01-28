/*
 
 timeDisplay.h
 
 Clock and system uptime-esque stuff on the left panel
 
 */

#pragma once
#include "ofMain.h"
#include "text.h"
#include <time.h>
#include <string.h>
#include "animated.h"
#include <vector>

class TimeDisplay : public Animated {
  
public:
  TimeDisplay();
  void update();
  void updateClockTime();
  void draw();
  
  void setPos(float x_, float y_);
  
  float x;
  float y;
  float w;
  float h;
  
  int t;
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  time_t currentTime;
  struct tm *localizedTime;
  
  time_t initTime;
  double diff_sec;
  
  string sec_s;
  string min_s;
  string hour_s;
  char* mon_s;
  string year_s;
  string uptime_s;
  
  int upperTextDelay;
  int lowerTextDelay;
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  AnimatedTickLine tline3;
  AnimatedText mainTime;
  vector<AnimatedText> upperTexts;
  vector<AnimatedText> lowerTexts;
};