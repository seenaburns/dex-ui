#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"

struct animation_event_t {
  int delay;
  int duration; // -1 if inf
  int id;
  int nextID; // loop by setting to self
};

class Animated {
public:
  Animated();
  void update();
  void updateTime();
  float getTime();
  
  void newEvent(int delay, int duration, int id, int nextID);
  
  void setEvents(vector<animation_event_t> events_);
  virtual void updateDependencyEvents();
  
  void setDelay(int delay_);
  int getDelay();
  virtual void updateDependencyDelays(int delay_);
  
  int currentEventIndex;
  animation_event_t currentEvent;
  
  vector<animation_event_t> events;
protected:
  float time;
  float delay;
  void updateCurrentEvent();
};

class AnimatedTickLine : public Animated {
public:
  AnimatedTickLine();
  void draw();
  void drawExtraTicks(float currentWidth, float centerX);
  
  float x;
  float y;
  float w;
  float duration;
//  float delay;
  
  ofColor color;
  float alpha;
  
  vector<float> extraTicks;
};

AnimatedTickLine newTickLine(float x, float y, float w, float dur, float delay, ofColor color);

class AnimatedText : public Animated {
public:
  AnimatedText();
  void draw();
  void setText(string fontPath, int size);
  
  float x;
  float y;
  float duration;
//  float delay;
  float rate;
  string s;
  bool fromRight;
  
  ofColor color;
  
  Text text;
private:
  void drawString();
};

AnimatedText newText(string s, int fontSize, float x, float y, float dur, float delay, ofColor color, bool fromRight);