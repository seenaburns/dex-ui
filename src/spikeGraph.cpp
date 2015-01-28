#include "spikeGraph.h"
#include "easing-utils.h"

SpikeGraph::SpikeGraph() {
  x = 0;
  y = 0;
  w = 240;
  h = 105;
  spikeWidth = 10;
  scounter = 0;
  speed = 1/4.0;
  for (int i = 0; i < 12; i++) {
    newSpike(0, 1, w-(i+1)*spikeWidth*2);
    newSpike(0, -1, w-(i+1)*spikeWidth*2);
  }
  
  maskShader.load("shadersGL3/null.vert","shadersGL3/spike.frag");
  
  tline1 = newTickLine(0, 0, w, 40, 0, COLOR_LINE);
  tline2 = newTickLine(0, h+30, w, 40, 0, COLOR_LINE);
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void SpikeGraph::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void SpikeGraph::update() {
  if (currentEvent.id != 0 || getTime() > 100) {
    updateSpikePositions();
    
    // Create new spikes
    if (needsNewSpike()) {
      if (scounter % 2 == 0) {
        newSpike(ofRandom(50), 1, w);
        newSpike(ofRandom(50), -1, w);
      } else {
        newSpike(0, 1, w);
        newSpike(0, -1, w);
      }
      scounter += 1;
    }
    
    // Remove spikes
    removeOldSpikes();
  }
  updateTime();
}

void SpikeGraph::draw() {
  update();
  
  ofPushMatrix();
  {
    ofTranslate(x, y);

    tline1.draw();
    tline2.draw();
      
    for (int i = 0; i < texts.size(); i++)
      texts[i].draw();
   
    // Draw box
    if (currentEvent.id == 0) {
      // Intro
      boxIntro();
    } else {
      ofNoFill();
      ofSetColor(COLOR_LINE,100);
      for (float i = 0.5; i <= w+0.5; i+=15)
        ofLine(i,15,i,h+15);
      for (float i = 0.5; i <= h+0.5; i+=15)
        ofLine(0,i+15,w,i+15);
    }
    
    // Draw spikes
    ofTranslate(0, 15);
    maskShader.begin();
    float absx = 1515;
    
    // Sweep mask from right to left on intro
    if (currentEvent.id == 0) {
      float maskW = easeOut(getTime()-120, w, 0, 50);
      maskShader.setUniform1f("abspos", absx+maskW);
      maskShader.setUniform1f("size", w-maskW);
    } else {
      maskShader.begin();
      maskShader.setUniform1f("abspos", absx);
      maskShader.setUniform1f("size", w);
    }
    
    ofNoFill();
    ofSetColor(COLOR_95);
    ofBeginShape();
    for (int i = 0; i < spikesUp.size(); i++)
      drawSpike(spikesUp[i]);
    ofEndShape();
    ofBeginShape();
    for (int i = 0; i < spikesDown.size(); i++)
      drawSpike(spikesDown[i]);
    ofEndShape();
    maskShader.end();
  }
  ofPopMatrix();
}

void SpikeGraph::drawSpike(spike s) {
  float ybase = 0;
  if (s.direction == 1)
    ybase = h/2;
  else
    ybase = h/2;
  float c1y = ybase+s.height*0.1*s.direction;
  float c2y = ybase+s.height*0.3*s.direction;
  float c1x = spikeWidth*0.1;
  float c2x = spikeWidth*0.05;

  ofVertex(s.x,ybase);
  ofBezierVertex(ofPoint(s.x+spikeWidth-c1x,c1y),
                 ofPoint(s.x+spikeWidth-c2x,c2y),
                 ofPoint(s.x+spikeWidth,ybase+s.height*s.direction));
  ofBezierVertex(ofPoint(s.x+spikeWidth+c2x,c2y),
                 ofPoint(s.x+spikeWidth+c1x,c1y),
                 ofPoint(s.x+spikeWidth*2,ybase));
}

void SpikeGraph::newSpike(float height, float dir, float x) {
  spike s;
  s.height = height;
  s.direction = dir;
  s.x = x;
  
  if (dir == 1)
    spikesDown.push_back(s);
  else
    spikesUp.push_back(s);
}

void SpikeGraph::updateSpikePositions() {
  for (int i = 0; i < spikesDown.size(); i++)
    spikesDown[i].x -= speed;
  for (int i = 0; i < spikesUp.size(); i++)
    spikesUp[i].x -= speed;
}

bool SpikeGraph::needsNewSpike() {
  return spikesDown.size() == 0 || spikesDown[spikesDown.size()-1].x < 240-spikeWidth*2;
}

void SpikeGraph::removeOldSpikes() {
  // Spikes Down
  if (spikesDown[0].x < -spikeWidth*2) {
    for (int i = 0; i < spikesDown.size()-1; i++)
      spikesDown[i] = spikesDown[i+1];
    spikesDown.pop_back();
  }
  
  // Spikes Up
  if (spikesUp[0].x < -spikeWidth*2) {
    for (int i = 0; i < spikesUp.size()-1; i++)
      spikesUp[i] = spikesUp[i+1];
    spikesUp.pop_back();
  }
}

void SpikeGraph::updateDependencyDelays(int delay_) {
  tline1.setDelay(delay_);
  tline2.setDelay(delay_-10);
  
  int textDelay = -105;
  int textDelays[2] = {0,-5};
  for (int i = 0; i < texts.size(); i++)
    texts[i].setDelay(delay_+textDelay+textDelays[i]);
}

void SpikeGraph::updateDependencyEvents() {
  tline1.setEvents(events);
  tline2.setEvents(events);
  
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}

void SpikeGraph::boxIntro() {
  int boxdelay = -50;
  int boxdurw = 40;
  int boxdurh = 40;
  
  // Boxes
  float boxh = h;
  float boxw = w;
  float tempBoxw = easeInOut(getTime()+boxdelay, 0, boxw, boxdurw);
  float tempBoxh = easeInOut(getTime()+boxdelay-boxdurw/2, 0, boxh, boxdurh);
  ofNoFill();
  ofSetColor(COLOR_LINE,100);
  for (float i = 0.5; i <= w+0.5; i+=15)
    ofLine(i,15,i,15+tempBoxh);
  for (float i = 0.5; i <= h+0.5; i+=15)
    ofLine(0,i+15,tempBoxw,i+15);
}
