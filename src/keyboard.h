#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "animated.h"

#define KEYBOARD_COLOR COLOR_175

class Key : public Animated {
public:
  Key();
  void setPos(float x_, float y_);
  void setString(string s_);
  void setTextSize(int size);
  
  void update();
  void draw();
  void press(int pressedKeyCode);
  void setDelay(int delay_);
  
  ofTrueTypeFont font;
  float x, y, w, h;
  string s;
  bool debug;
  int keynum; // used for intro animation offset
  float randdelay;
  int keycode; // used for pressing
private:
  float s_xoff, s_yoff;
  float xpadding, ypadding;
  
  void updateBounds();
  
  void debug_draw_bounding_rect();
};

class Spacebar : public Animated {
public:
  Spacebar();
  void setPos(float x_, float y_);
  void draw();
  void press();
  void update();
  
  float x, y, w, h;
  float r;
};

class KeyRow : public Animated {
public:
  KeyRow();
  void setPos(float x_, float y_);
  void setKeys(string s);
  
  void draw();
  float x, y, w, h;
  float xpadding_small;
  float xpadding_large;
  bool debug;
  void toggleDebug();
  void initializeAnimatedItems();
  void press(int pressedKeyCode);
  
  void updateDependencyDelays(int delay_);
private:
  vector<Key> keys;
  
  void updateBounds();
  void keysFromString(string s);
  void addKey(string s, float x_, float y_, int keynum);
  float getKeyPadding(Key &k);
  
  void debug_draw_bounding_rect();
};

class KeyDetector {
public:
  KeyDetector();
  int readKeyReleased();

private:
  int fd;
};

class Keyboard : public Animated {
public:
  Keyboard();
  void setPos(float x_, float y_);
  
  void draw();
  void toggleDebug();
  float x, y, w, h;

  void updateDependencyDelays(int delay_);
private:
  KeyRow kr1;
  KeyRow kr2;
  KeyRow kr3;
  KeyRow kr4;
  Spacebar space;
  KeyDetector kd;
};

int mapStringToKeyCode(string key);