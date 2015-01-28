#include "timeDisplay.h"
#include "graphics-utils.h"

TimeDisplay::TimeDisplay() {
  // Reset if being called again
  upperTexts.clear();
  lowerTexts.clear();
  
  setPos(0,0);
  w = 240;
  h = 90;
  
  ::time(&currentTime);
  ::time(&initTime);
  localizedTime = localtime (&currentTime);
  
  year_s = ofToString(localizedTime->tm_year+1900);
  mon_s = (char *) malloc(10*sizeof(char));
  strftime(mon_s, 10, "%b %d", localizedTime);
  for (int i = 0; i < 10; i++)
    mon_s[i] = toupper(mon_s[i]);
  
  // Lines
  tline1.w = w;
  tline1.duration = 40;
  
  tline2.w = w;
  tline2.y = 60;
  tline2.duration = 40;
  tline2.extraTicks.push_back(3*GRID_SIZE+0.5);
  tline2.extraTicks.push_back(4*GRID_SIZE+0.5);
  tline2.extraTicks.push_back(8*GRID_SIZE+0.5);
  tline2.extraTicks.push_back(9*GRID_SIZE+0.5);
  tline2.extraTicks.push_back(13*GRID_SIZE+0.5);
  tline2.extraTicks.push_back(14*GRID_SIZE+0.5);
  
  tline3.w = w;
  tline3.y = 90;
  tline3.duration = 40;
  tline3.extraTicks.push_back(3*GRID_SIZE+0.5);
  tline3.extraTicks.push_back(4*GRID_SIZE+0.5);
  tline3.extraTicks.push_back(8*GRID_SIZE+0.5);
  tline3.extraTicks.push_back(9*GRID_SIZE+0.5);
  tline3.extraTicks.push_back(13*GRID_SIZE+0.5);
  tline3.extraTicks.push_back(14*GRID_SIZE+0.5);
  
  // Text
  int textDelay = 0;
  mainTime = newText("SYSTEM SUMMARY", 37,
                     5, 12,
                     20, delay+textDelay-80,
                     COLOR_175,
                     false);
  mainTime.text.ofFont.setSpaceSize(0.4);
  mainTime.setEvents(events);
  
  // Upper and lower texts
  upperTextDelay=-80;
  lowerTextDelay=-65;
  int upper_text_y = 60+7;
  int lower_text_y = 75+2;
  int inset = 5;
  
  string upperStrings[4] = {year_s, "UPTIME", "SYSTEM", "V"};
  string lowerStrings[4] = {mon_s, uptime_s, "ONLINE", "0.1b"};
  int xpositions[4] = {0.0+inset, 4*GRID_SIZE+inset, 9*GRID_SIZE+inset, 14*GRID_SIZE+inset};
  
  // Upper
  for (int i = 0; i < 4; i++) {
    AnimatedText newT = newText(upperStrings[i], 7,
                                xpositions[i], upper_text_y,
                                20, upperTextDelay,
                                COLOR_75,
                                false);
    upperTexts.push_back(newT);
  }
  
  // Lower
  for (int i = 0; i < 4; i++) {
    AnimatedText newT = newText(lowerStrings[i], 7,
                                xpositions[i], lower_text_y,
                                20, lowerTextDelay,
                                COLOR_135,
                                false);
    lowerTexts.push_back(newT);
  }
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void TimeDisplay::update() {
  if ((int)time%60 == 0) {
    updateClockTime();
  }
  updateTime();
}

void TimeDisplay::updateClockTime() {
  // Only get real time every 10 seconds or if minute is going to change
  if (t%600 != 0 && localizedTime->tm_sec < 59) {
    localizedTime->tm_sec += 1;
    diff_sec += 1;
  } else {
    ::time(&currentTime);
    localizedTime = localtime (&currentTime);
    diff_sec = difftime(currentTime, initTime);
  }
  
  // Update time strings
  hour_s = ofToString(localizedTime->tm_hour);
  min_s = ofToString(localizedTime->tm_min);
  sec_s = ofToString(localizedTime->tm_sec);
  
  // Pad 0's if necessary
  if (localizedTime->tm_hour < 10)
    hour_s = "0" + hour_s;
  if (localizedTime->tm_min < 10)
    min_s = "0" + min_s;
  if (localizedTime->tm_sec < 10)
    sec_s = "0" + sec_s;
  
  uptime_s = ofToString((int)(diff_sec/3600)%99);
  uptime_s += ":" + ofToString((int)(diff_sec/60)%60);
  uptime_s += ":" + ofToString((int)diff_sec%60);
}

void TimeDisplay::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    // INTRO or MAIN
    ofSetColor(COLOR_LINE);
    
    // Top of time
    tline1.draw();
    // Top of info
    tline2.draw();
    // Bottom of info
    tline3.draw();
    
    mainTime.s = hour_s + " : " + min_s + " : " + sec_s;
    mainTime.draw();
    
    // Update uptime
    lowerTexts[1].s = uptime_s;
    
    // Draw texts
    for (int i = 0; i < upperTexts.size(); i++) {
      upperTexts[i].draw();
      lowerTexts[i].draw();
    }
  }
  ofPopMatrix();
}

void TimeDisplay::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void TimeDisplay::updateDependencyDelays(int delay_) {
  tline1.setDelay(delay_);
  tline2.setDelay(delay_-5);
  tline3.setDelay(delay_-10);
  mainTime.setDelay(delay_-80);
  for (int i = 0; i < upperTexts.size(); i++) {
    upperTexts[i].setDelay(delay_+upperTextDelay);
    lowerTexts[i].setDelay(delay_+lowerTextDelay);
  }
}

void TimeDisplay::updateDependencyEvents() {
  tline1.setEvents(events);
  tline2.setEvents(events);
  tline3.setEvents(events);
  mainTime.setEvents(events);
  for (int i = 0; i < upperTexts.size(); i++) {
    upperTexts[i].setEvents(events);
    lowerTexts[i].setEvents(events);
  }
}