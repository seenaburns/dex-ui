#include "keyboard.h"
#include <string>
#include "easing-utils.h"

// For keyinput
/*#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
*/

Key::Key() {
  s_xoff = 0;
  s_yoff = 0;
  xpadding = 10;
  ypadding = 10;
  keynum = 0;
  randdelay = ofRandom(20);
  
  setPos(0,0);
  setTextSize(12);
  setString("x");
  debug = false;
  
  // Animation settings
  events.clear();
  newEvent(0, 200, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  newEvent(0, 20, 2, 1); // keypress
  currentEvent = events[0];
}

void Key::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Key::setString(string s_) {
  s = s_;
  keycode = mapStringToKeyCode(s);
  updateBounds();
}

void Key::setTextSize(int size) {
  font.loadFont(MAIN_FONT, size);
  updateBounds();
}

void Key::setDelay(int delay_) {
  events[0].delay = delay_ - keynum*8 - randdelay;
  currentEvent = events[0];
}

void Key::draw() {
  updateTime();
  
  ofPushMatrix();
  {
    ofTranslate(x,y);
    
    if (currentEvent.id == 0) {
      // Intro
      if (getTime() > 0) {
        float t = easeQuinticInOutBack(getTime(), 0, 1, 60);
        t *= flicker(getTime()-5,20,5);
        ofColor base = COLOR_15;
        base.lerp(KEYBOARD_COLOR,t);
        ofSetColor(base);
        font.drawString(s, s_xoff, s_yoff);
      }
    } else if (currentEvent.id == 2) {
      float fillalpha = easeInOut(getTime(),255,0,20);
      fillalpha *= flicker(getTime(),6,3);
      // Draw rect
      ofFill();
      ofSetColor(KEYBOARD_COLOR, fillalpha);
      ofRectRounded(0,0,w,h,3);
      
      // Draw text
//      float textalpha = easeInOut(getTime(),0,150,20);
//      ofSetColor(KEYBOARD_COLOR, textalpha);
      font.drawString(s, s_xoff, s_yoff);
      
    } else if (currentEvent.id == 1) {
      ofSetColor(KEYBOARD_COLOR);
      font.drawString(s, s_xoff, s_yoff);
      
      if (debug) {
        debug_draw_bounding_rect();
      }
    }
  }
  ofPopMatrix();
}

void Key::press(int pressedKeyCode) {
  if (pressedKeyCode != keycode)
    return;
  if (currentEvent.id != 0) {
    currentEvent = events[2];
    time = 0;
  }
}

void Key::updateBounds() {
  ofRectangle bounds = font.getStringBoundingBox(s, 0, 0);
  w = bounds.width+xpadding*2;
  h = 35; //bounds.height+ypadding*2;
  s_yoff = (h-bounds.height)/2.0+bounds.height; //bounds.height+ypadding;
  s_xoff = xpadding;
}

void Key::debug_draw_bounding_rect() {
  ofNoFill();
  ofSetColor(255);
  ofRect(0,0,w,h);
}

//
// Spacebar
//
Spacebar::Spacebar() {
  setPos(0, 0);
  w = 420;
  h = 23;
  r = 4;
  
  // Animation settings
  events.clear();
  newEvent(0, 200, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  newEvent(0, 20, 2, 1); // keypress
  currentEvent = events[0];
}

void Spacebar::setPos(float x_, float y_) {
  x = x_+0.5;
  y = y_+0.5;
}

void Spacebar::draw() {
  updateTime();
  
  ofNoFill();
  if (currentEvent.id == 0) {
    // Intro
    float rectw = easeInOut(getTime(), 0, w, 30);
    float recth = easeInOut(getTime()-15, 0, h, 15);
    float t = easeQuinticInOutBack(getTime(), 0, 1, 60);
    t *= flicker(getTime()-15,10,5);
    ofColor base = COLOR_15;
    base.lerp(KEYBOARD_COLOR,t);
    ofSetColor(base);
    ofRectRounded(ofPoint(x+(w-rectw)/2,y+(h-recth)/2), rectw, recth, r, r, r, r);
  } else if (currentEvent.id == 2) {
    float fillalpha = easeInOut(getTime(),255,0,20);
    fillalpha *= flicker(getTime(),6,3);
    
    // Draw fill
    ofSetColor(KEYBOARD_COLOR, fillalpha);
    ofFill();
    ofRectRounded(ofPoint(x,y), w, h, r, r, r, r);
    
    // Draw stroke
    ofSetColor(KEYBOARD_COLOR);
    ofNoFill();
    ofRectRounded(ofPoint(x,y), w, h, r, r, r, r);
  } else if (currentEvent.id == 1) {
    ofSetColor(KEYBOARD_COLOR);
    ofRectRounded(ofPoint(x,y), w, h, r, r, r, r);
  }
}

void Spacebar::press() {
  if (currentEvent.id != 0) {
    currentEvent = events[2];
    time = 0;
  }
}

//
// KeyRow
//
KeyRow::KeyRow() {
  setPos(0,0);
  setKeys("x|x|x");
  xpadding_small = 30;
  xpadding_large = 30;
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyDelays(getDelay());
}

void KeyRow::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void KeyRow::setKeys(string s) {
  keys.clear();
  keysFromString(s);
  updateBounds();
}

void KeyRow::draw() {
  updateTime();
  ofPushMatrix();
  {
    ofTranslate(x,y);
    
    for (int i = 0; i < keys.size(); i++)
      keys[i].draw();
      
    if (debug) {
      debug_draw_bounding_rect();
    }
  }
  ofPopMatrix();
}

void KeyRow::toggleDebug() {
  debug = !debug;
  for (int i = 0; i < keys.size(); i++)
    keys[i].debug = debug;
}

void KeyRow::updateBounds() {
  if (keys.size() == 0) {
    w = 0;
    h = 0;
    return;
  }
  w = keys[keys.size()-1].x + keys[keys.size()-1].w;
  h = keys[0].h;
}

void KeyRow::keysFromString(string s) {
  size_t pos = 0;
  string token;
  string delimiter = "|";
  float xoff = 0;
  int i = 0;
  while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    addKey(token, xoff, 0, i);
    xoff += getKeyPadding(keys[keys.size()-1]);
    s.erase(0, pos + delimiter.length());
    i++;
  }
  
  updateDependencyDelays(getDelay());
}

void KeyRow::addKey(string s, float x_, float y_, int keynum) {
  Key k;
  k.setPos(x_, y_);
  k.setString(s);
  if (s.length() > 1)
    k.setTextSize(10);
  else
    k.setTextSize(14);
  k.keynum = abs(keynum-5);
  keys.push_back(k);
}

float KeyRow::getKeyPadding(Key &k) {
  float pad = k.w;
  if (k.s.length() > 1)
    pad += xpadding_small;
  else
    pad += xpadding_large;
  return pad;
}

void KeyRow::debug_draw_bounding_rect() {
  ofNoFill();
  ofSetColor(255,0,0,150);
  ofRect(0,0,w,h);
}

void KeyRow::press(int pressedKeyCode) {
  for (int i = 0; i < keys.size(); i++)
    keys[i].press(pressedKeyCode);
}

void KeyRow::updateDependencyDelays(int delay_) {
  for (int i = 0; i < keys.size(); i++)
    keys[i].setDelay(delay_);
}


//
// KEYBOARD
//
Keyboard::Keyboard() {
  setPos(0,0);
  w = 780;
  h = 240;
  kr1.setPos(0, 0);
  kr1.setKeys("ESC|1|2|3|4|5|6|7|8|9|0|-|BACK|");
  
  kr2.setPos(25, 45);
  kr2.xpadding_small = 20;
  kr2.setKeys("TAB|Q|W|E|R|T|Y|U|I|O|P|( )|");
  
  kr3.setPos(40, 90);
  kr3.xpadding_small = 20;
  kr3.setKeys("CAPS|A|S|D|F|G|H|J|K|L|;|ENTER|");
  
  kr4.setPos(25, 135);
  kr4.xpadding_small = 20;
  kr4.setKeys("SHIFT|Z|X|C|V|B|N|M|,|.|/|SHIFT|");
  
  space.setPos(175, 190);

  // Animation settings
  events.clear();
  newEvent(0, 200, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyDelays(getDelay());
}

void Keyboard::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Keyboard::toggleDebug() {
  kr1.toggleDebug();
  kr2.toggleDebug();
  kr3.toggleDebug();
  kr4.toggleDebug();
}

void Keyboard::draw() {
  updateTime();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    // ofSetColor(255);
    // ofDrawBitmapString(ofToString(time), 0,-20);
    
    int key = 1; 
    while (key >= 0) {
      key = kd.readKeyReleased();
      if (key > 0) {
        // cout << key << endl;
        kr1.press(key);
        kr2.press(key);
        kr3.press(key);
        kr4.press(key);
        if (key == 57)
          space.press();
      }
    }

    kr1.draw();
    kr2.draw();
    kr3.draw();
    kr4.draw();
    space.draw();
  }
  ofPopMatrix();
}

void Keyboard::updateDependencyDelays(int delay_) {
  kr1.setDelay(delay_);
  kr2.setDelay(delay_);
  kr3.setDelay(delay_);
  kr4.setDelay(delay_);
  space.setDelay(delay_-50);
}

KeyDetector::KeyDetector() {
  // Follow http://stackoverflow.com/questions/20943322/accessing-keys-from-linux-input-device
/*  //const char *devfname = "/dev/input/...";

  // Open devfname
  fd = open(devfname, O_RDONLY);
  if (fd == -1)
    fprintf(stderr, "Cannot open %s: %s.\n", devfname, strerror(errno));

  // Make nonblocking
  // Get current flags
  int flags = fcntl(fd, F_GETFL);
  int err = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (err == -1)
    fprintf(stderr, "Could not make nonblocking\n");*/
}

int KeyDetector::readKeyReleased() {
/*  struct input_event ev;
  ssize_t n;
  n = read(fd, &ev, sizeof ev);
  if (n == (ssize_t)-1) {
    if (errno == EINTR)
      return 0;
    else
      return -1;
  } else {
    if (n != sizeof ev) {
      errno = EIO;
      return -1;
    }
  }
  if (ev.type == EV_KEY && ev.value == 1) {
    // cout << (int) ev.code << endl;
    return (int)ev.code;
  }
  return 0;*/
  return -1;
}

int mapStringToKeyCode(string key) {
  if (key == "ESC") return 1;
  else if (key == "1") return 2;
  else if (key == "2") return 3;
  else if (key == "3") return 4;
  else if (key == "4") return 5;
  else if (key == "5") return 6;
  else if (key == "6") return 7;
  else if (key == "7") return 8;
  else if (key == "8") return 9;
  else if (key == "9") return 10;
  else if (key == "0") return 11;
  else if (key == "-") return 12;
  else if (key == "BACK") return 14;

  else if (key == "TAB") return 15;
  else if (key == "Q") return 16;
  else if (key == "W") return 17;
  else if (key == "E") return 18;
  else if (key == "R") return 19;
  else if (key == "T") return 20;
  else if (key == "Y") return 21;
  else if (key == "U") return 22;
  else if (key == "I") return 23;
  else if (key == "O") return 24;
  else if (key == "P") return 25;
  else if (key == "( )") return 26;

  else if (key == "CAPS") return 58;
  else if (key == "A") return 30;
  else if (key == "S") return 31;
  else if (key == "D") return 32;
  else if (key == "F") return 33;
  else if (key == "G") return 34;
  else if (key == "H") return 35;
  else if (key == "J") return 36;
  else if (key == "K") return 37;
  else if (key == "L") return 38;
  else if (key == ";") return 39;
  else if (key == "ENTER") return 28;

  else if (key == "SHIFT") return 42;
  else if (key == "Z") return 44;
  else if (key == "X") return 45;
  else if (key == "C") return 46;
  else if (key == "V") return 47;
  else if (key == "B") return 48;
  else if (key == "N") return 49;
  else if (key == "M") return 50;
  else if (key == ",") return 51;
  else if (key == ".") return 52;
  else if (key == "/") return 53;

  return 0;
}

