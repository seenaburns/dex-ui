#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"
#include "text.h"
#include "animated.h"

struct spike {
  float height;
  float direction;
  float x;
};

class SpikeGraph : public Animated {
public:
  SpikeGraph();
  void update();
  void draw();
  void drawSpike(spike s);
  void newSpike(float height, float dir, float x);
  void setPos(float x_, float y_);
  
  float x,y,w,h;
  float spikeWidth;
  
  void updateDependencyEvents();
  void updateDependencyDelays(int delay_);
private:
  int scounter;
  float speed;
  
  // Assumed to match in x positions
  vector<spike> spikesDown;
  vector<spike> spikesUp;
  
  void updateSpikePositions();
  bool needsNewSpike();
  void removeOldSpikes();
  
  ofShader maskShader;
  
  AnimatedTickLine tline1;
  AnimatedTickLine tline2;
  vector<AnimatedText> texts;
  
  void boxIntro();
};