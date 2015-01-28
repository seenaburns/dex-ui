#include "animated.h"
#include "easing-utils.h"

Animated::Animated() {
  // Default variables and events
  // derived classes call automatically
  newEvent(0, -1, 0, 0);
  
  time = 0;
  delay = 0;
  currentEvent = events[0];
}

void Animated::updateTime() {
  // Loop or switch events if necessary
  if (currentEvent.duration != -1 && time + 1 >= currentEvent.duration) {
    time = 0;
    updateCurrentEvent();
  }
  
  time += 1;
}

void Animated::updateCurrentEvent() {
  int nextID = currentEvent.nextID;
  
  // If loop, don't change currentEvent
  if (nextID == currentEvent.id)
    return;
  
  // Otherwise find next id
  for (int i = 0; i < events.size(); i++) {
    animation_event_t e = events[i];
    if (e.id == currentEvent.nextID) {
      currentEvent = e;
      break;
    }
  }
}

float Animated::getTime() {
  return time+currentEvent.delay;
}

void Animated::newEvent(int delay, int duration, int id, int nextID) {
  animation_event_t e = animation_event_t();
  e.delay = delay;
  e.duration = duration;
  e.id = id;
  e.nextID = nextID;
  events.push_back(e);
}

void Animated::setEvents(vector<animation_event_t> events_) {
  events = events_;
  currentEvent = events[0];
  updateDependencyEvents();
}

void Animated::updateDependencyEvents() {
}

void Animated::setDelay(int delay_) {
  // By default update event0's delay, assumed to be intro
  events[0].delay = delay_;
  currentEvent = events[0];
  updateDependencyDelays(delay_);
}

int Animated::getDelay() {
  // By default return event0's delay
  return events[0].delay;
}

void Animated::updateDependencyDelays(int delay_) {
}

//
//
// ANIMATED TICK LINE
//
//
AnimatedTickLine::AnimatedTickLine() {
  x = 0;
  y = 0;
  w = 240;
  duration = 50;
  delay = 0;
  color = COLOR_LINE;
  alpha = 255;
  
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
}

void AnimatedTickLine::draw() {
  updateTime();
  
  if (currentEvent.id == 0 && getTime() > 0) {
    // Intro
    float temp_width = easeInOut(getTime(), 0, w, duration);
    float centerX = x+(w-temp_width)/2;
    ofSetColor(color, alpha);
    tick_line(centerX, centerX+temp_width, y);
    drawExtraTicks(temp_width, centerX);
  } else if (currentEvent.id == 1) {
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
//
// ANIMATED TEXT
//
///
AnimatedText::AnimatedText() {
  x = 0;
  y = 0;
  duration = 50;
  delay = 0;
  rate = 5;
  color = COLOR_LINE;
  fromRight = false;
  
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
}

void AnimatedText::draw() {
  updateTime();
  
  if (getTime() < 0)
    return;
  
  if (currentEvent.id == 0) {
    // Intro
    float alpha = 255*flicker(getTime(), duration, rate);
    ofSetColor(color, alpha);
    drawString();
  } else{
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
