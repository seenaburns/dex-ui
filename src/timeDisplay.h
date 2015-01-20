/*
 
 timeDisplay.h
 
 Clock and system uptime-esque stuff on the left side info bar
 
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
  void setDelay(float delay_);
  
  float x;
  float y;
  float w;
  float h;
  
  int t;
  
  void initializeAnimatedItems();
private:
  Text font36;
  Text font7;
  
  time_t currentTime;
  struct tm *localizedTime;
  
  time_t initTime;
  double diff_sec;
  
  string sec_s;
  string min_s;
  string hour_s;
  char* mon_s;
  string year_s;
//  char* uptime_s;
  string uptime_s;
  
  float delay;
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  AnimatedTickLine tline3;
  AnimatedText mainTime;
  vector<AnimatedText> upperText;
  vector<AnimatedText> lowerText;
  
  void initializeText();
};