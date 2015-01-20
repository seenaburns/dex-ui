#include "timeDisplay.h"
#include "graphics-utils.h"

TimeDisplay::TimeDisplay() {
  setPos(0,0);
  w = 240;
  h = 90;
  
  font36 = Text();
  font36.setFont(MAIN_FONT, 36);
  
  font7 = Text();
  font7.setFont(MAIN_FONT, 7);
  
  ::time(&currentTime);
  ::time(&initTime);
  localizedTime = localtime (&currentTime);
  
  year_s = ofToString(localizedTime->tm_year+1900);
//  mon_s = ofToString(localizedTime->tm_mday);
  mon_s = (char *) malloc(10*sizeof(char));
  strftime(mon_s, 10, "%b %d", localizedTime);
  for (int i = 0; i < 10; i++)
    mon_s[i] = toupper(mon_s[i]);
  
  //  uptime_s = (char *) malloc(10*sizeof(char));
  
  initAnimated();
  newEvent(0, 300, 0, true); // intro
  newEvent(300, -1, 1, false); // main
  delay = 0;
  
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
  
  tline1.setEvents(events);
  tline2.setEvents(events);
  tline3.setEvents(events);
  
  initializeText();
  setDelay(0);
}

void TimeDisplay::update() {
  if ((int)time%60 == 0) {
    updateClockTime();
  }
  Animated::update();
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

  hour_s = ofToString(localizedTime->tm_hour);
  min_s = ofToString(localizedTime->tm_min);
  sec_s = ofToString(localizedTime->tm_sec);
  
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
    
    if (getCurrentEventID() == 0 || getCurrentEventID() == 1) {
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
      
      for (int i = 0; i < upperText.size(); i++)
        upperText[i].draw();
      for (int i = 0; i < lowerText.size(); i++) {
        if (i == 1)
          lowerText[i].s = uptime_s;
        lowerText[i].draw();
      }
      
    } else {
      // ???
    }
  }
  ofPopMatrix();
}

void TimeDisplay::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void TimeDisplay::setDelay(float delay_) {
  delay = delay_;
  tline1.setDelay(delay);
  tline2.setDelay(delay-5);
  tline3.setDelay(delay-10);
  initializeText();
}

void TimeDisplay::initializeText() {
  float textDelay = 0;
  mainTime = newText("SYSTEM SUMMARY", 37,
                     5, 12,
                     20, delay+textDelay-80,
                    COLOR_175,
                    false);
  mainTime.text.ofFont.setSpaceSize(0.4);
  mainTime.setEvents(events);
  
  upperText.clear();
  lowerText.clear();
  int upper_text_y = 60+7;
  int lower_text_y = 75+2;
  int inset = 5;
  vector<string> upperStrings;
  vector<string> lowerStrings;
  vector<float> xpositions;
  upperStrings.push_back(year_s);
  lowerStrings.push_back(mon_s);
  upperStrings.push_back("UPTIME");
  lowerStrings.push_back(uptime_s);
  upperStrings.push_back("SYSTEM");
  lowerStrings.push_back("ONLINE");
  upperStrings.push_back("V");
  lowerStrings.push_back("0.1b");
  xpositions.push_back(0.0+inset);
  xpositions.push_back(4*GRID_SIZE+inset);
  xpositions.push_back(9*GRID_SIZE+inset);
  xpositions.push_back(14*GRID_SIZE+inset);
  
  // Upper
  for (int i = 0; i < upperStrings.size(); i++) {
    AnimatedText newText;
    newText.setText(MAIN_FONT, 7);
    newText.color = COLOR_75;
    newText.duration = 20;
    newText.setDelay(delay+textDelay-50);
    newText.x = xpositions[i];
    newText.y = upper_text_y;
    newText.s = upperStrings[i];
    newText.setEvents(events);
    upperText.push_back(newText);
  }
  // Lower
  for (int i = 0; i < lowerStrings.size(); i++) {
    AnimatedText newText;
    newText.setText(MAIN_FONT, 7);
    newText.color = COLOR_135;
    newText.duration = 20;
    newText.setDelay(delay+textDelay-65);
    newText.x = xpositions[i];
    newText.y = lower_text_y;
    newText.s = lowerStrings[i];
    newText.setEvents(events);
    lowerText.push_back(newText);
  }
}

void TimeDisplay::initializeAnimatedItems() {
  tline1.setEvents(events);
  tline2.setEvents(events);
  tline3.setEvents(events);
}