#include "animated.h"
#include "easing-utils.h"

Animated::Animated() {
  initAnimated();
}

void Animated::initAnimated() {
  time = 0;
  delay = 0;
}

void Animated::update() {
  updateTime();
}

void Animated::updateTime() {
  // Loop if necessary
  int index = getCurrentEventIndex();
  if (index >= 0) {
    animation_event_t e = events[index];
    if (e.loop && time + 1 >= e.start + e.duration)
      time = e.start;
  }
  
  time += 1;
}

float Animated::getTime() {
  return time+delay;
}

// Return index (for events) which event contains time
// -1 if no events found
int Animated::getCurrentEventIndex() {
  for (int i = 0; i < events.size(); i++) {
    animation_event_t e = events[i];
    if (time >= e.start && (time < e.start + e.duration || e.duration == -1))
      return i;
  }
  return -1;
}

int Animated::getCurrentEventID() {
  int index = getCurrentEventIndex();
  
  // Check if no current event
  if (index < 0)
    return index;
  
  // Else return ide
  animation_event_t e = events[index];
  return e.id;
}

void Animated::newEvent(float start, float duration, int id, bool loop) {
  animation_event_t e = animation_event_t();
  e.start = start;
  e.duration = duration;
  e.id = id;
  e.loop = loop;
  events.push_back(e);
}

void Animated::setEvents(vector<animation_event_t> events_) {
  events = events_;
  initializeAnimatedItems();
}

void Animated::setDelay(float delay_) {
  delay = delay_;
  initializeAnimatedItems();
}

float Animated::getDelay() {
  return delay;
}

void Animated::initializeAnimatedItems() {
}

//
// ANIMATED TICK LINE
//
AnimatedTickLine::AnimatedTickLine() {
  x = 0;
  y = 0;
  w = 240;
  duration = 50;
  delay = 0;
  color = COLOR_LINE;
  alpha = 255;
  
  initAnimated();
  newEvent(0, 300, 0, true); // intro
  newEvent(300, -1, 1, false); // main
}

void AnimatedTickLine::draw() {
  updateTime();
  
  if (getCurrentEventID() == 0 && getTime() > 0) {
    // Intro
    float temp_width = easeInOut(getTime(), 0, w, duration);
    float centerX = x+(w-temp_width)/2;
    ofSetColor(color, alpha);
    tick_line(centerX, centerX+temp_width, y);
    drawExtraTicks(temp_width, centerX);
  } else if (getCurrentEventID() == 1) {
    // Main
    ofSetColor(color, alpha);
    tick_line(x, x+w, y);
    drawExtraTicks(w,x);
  }
}

void AnimatedTickLine::drawExtraTicks(float currentWidth, float centerX) {
  // only for intro
  for (int i = 0; i < extraTicks.size(); i++) {
    float xpos = centerX + extraTicks[i] * currentWidth/w;
    tick(xpos, y);
  }
}

AnimatedTickLine newTickLine(float x, float y, float w, float dur, float delay, ofColor color) {
  AnimatedTickLine line = AnimatedTickLine();
  line.x = x;
  line.y = y;
  line.w = w;
  line.duration = dur;
  line.setDelay(delay);
  line.color = color;
  return line;
}

//
// ANIMATED TEXT
//
AnimatedText::AnimatedText() {
  x = 0;
  y = 0;
  duration = 50;
  delay = 0;
  rate = 5;
  color = COLOR_LINE;
  fromRight = false;
  
  initAnimated();
  newEvent(0, 300, 0, true); // intro
  newEvent(300, -1, 1, false); // main
}

void AnimatedText::draw() {
  updateTime();
  
  if (getCurrentEventID() == 0 && getTime() > 0) {
    // Intro
    float alpha = 255*flicker(getTime(), duration, rate);
    ofSetColor(color, alpha);
    drawString();
  } else if (getCurrentEventID() == 1) {
    // Main
    ofSetColor(color, 255);
    drawString();
  }
}

void AnimatedText::setText(string fontPath, int size) {
  text.setFont(fontPath, size);
}

void AnimatedText::drawString() {
  if (fromRight)
    text.drawStringFromTopRight(s, x, y);
  else
    text.drawString(s, x, y);
}

AnimatedText newText(string s, int fontSize, float x, float y, float dur, float delay, ofColor color, bool fromRight) {
  AnimatedText newText = AnimatedText();
  newText.setText(MAIN_FONT, fontSize);
  newText.s = s;
  newText.fromRight = fromRight;
  newText.color = color;
  newText.duration = dur;
  newText.setDelay(delay);
  newText.x = x;
  newText.y = y;
  return newText;
}