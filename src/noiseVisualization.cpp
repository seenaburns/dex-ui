#include "noiseVisualization.h"
#include "graphics-utils.h"
#include "easing-utils.h"

NoiseVisualization::NoiseVisualization() {
  x = 0;
  y = 0;
  w = 240;
  h = 8*GRID_SIZE;
  
  noiseShader.load("shadersGL3/noise");
  
  t = 0;
  update_x = 0;
  noise_off = ofRandom(100,1000);
  noise_w = w;
  noise_h = 6*GRID_SIZE;
  initTexture(1);
  
  tline1.w = w;
  tline1.duration = 40;
  
  tline2.y = h;
  tline2.w = w;
  tline2.duration = 40;
  
  texts.clear();
  texts.push_back(newText("SYSTEM MAP", 5,
                          5, 7,
                          10, 0,
                          COLOR_135,
                          false));
  texts.push_back(newText("NOISE VISUALIZATION", 5,
                          w-5, 7,
                          10, 0,
                          COLOR_55,
                          true));
  texts.push_back(newText("NORMAL", 5,
                          w-5, h-11,
                          10, 0,
                          COLOR_55,
                          true));
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 0); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void NoiseVisualization::update() {
  // Update every 5 frames, but wait until frame 100 in intro
  if ((int)t % 5 == 0 && (currentEvent.id != 0 || getTime() > 100)) {
    // Updating code
    unsigned char *pixels = displacementTexture.getPixels();
    for (int y = 0; y < texh; y+=5) {
      int i = y * texw + update_x;
      float n = ofNoise((noise_off+y)/50,(noise_off+update_x)/50);
      pixels[i] = easeIn(n, 0, 255, 1);
    }
    for (int y = 0; y < texh; y+=5) {
      for (int x = 0; x < texw; x+=5) {
        if (x < update_x || x > update_x+50) {
          int i = y * texw + x;
          pixels[i] = max(pixels[i]-3, 0);
        }
      }
    }
    displacementTexture.update();
    
    update_x -= 5;
    if (update_x < 0) {
      update_x = texw-5;
      noise_off += noise_off;
    }
  }
  
  t += 1;
  updateTime();
}

void NoiseVisualization::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    tline1.draw();
    tline2.draw();
    
    for (int i = 0; i < texts.size(); i++)
      texts[i].draw();
    
    // Draw noise, later in intro
    if (currentEvent.id != 0 || getTime() > 100)
      drawNoise();
  }
  ofPopMatrix();
}

void NoiseVisualization::drawNoise() {
  displacementTexture.getTextureReference().bind();
  
  ofPushMatrix();
  {
    ofTranslate(0,1*GRID_SIZE);
    ofSetColor(COLOR_95);
    
    noiseShader.begin();
    ofFill();
    ofRect(0, 0, noise_w, noise_h);
    noiseShader.end();
  }
  ofPopMatrix();
  
  displacementTexture.getTextureReference().unbind();
}

void NoiseVisualization::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void NoiseVisualization::initTexture(int descalar) {
  texw = noise_w/descalar;
  texh = noise_h/descalar;
  displacementTexture.allocate(texw, texh, OF_IMAGE_GRAYSCALE);
  
  unsigned char *pixels = displacementTexture.getPixels();
  memset(pixels, 0, texw*texh);
  
  /*for (int y = 0; y < texh; y+=5) {
    for (int x = 0; x < texw; x+=5) {
      int i = y * texw + x;
      pixels[i] = 0; //255*ofNoise(y/20.0,x/20.0);
    }
  }*/
  displacementTexture.update();
  
  update_x = texw-5;
}

void NoiseVisualization::updateDependencyDelays(int delay_) {
  tline1.setDelay(delay_);
  tline2.setDelay(delay_-5);
  int textDelay = -40;
  int textDelays[3] = {0,-5,-10};
  for (int i = 0; i < texts.size(); i++)
    texts[i].setDelay(delay_+textDelay+textDelays[i]);
}

void NoiseVisualization::updateDependencyEvents() {
  tline1.setEvents(events);
  tline2.setEvents(events);
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}
