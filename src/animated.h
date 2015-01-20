#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"

struct animation_event_t {
  float start;
  float duration; // -1 if inf
  int id;
  bool loop;
};

class Animated {
public:
  Animated();
  void update();
  void updateTime();
  float getTime();
  int getCurrentEventIndex();
  int getCurrentEventID();
  
  void newEvent(float start, float duration, int id, bool loop);
  virtual void initializeAnimatedItems();
  void setEvents(vector<animation_event_t> events_);
  
  void setDelay(float delay_);
  float getDelay();
  
  void initAnimated();
protected:
  vector<animation_event_t> events;
  
  float time;
  float delay;
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