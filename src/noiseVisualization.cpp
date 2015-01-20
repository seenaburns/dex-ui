#include "noiseVisualization.h"
#include "graphics-utils.h"
#include "easing-utils.h"

NoiseVisualization::NoiseVisualization() {
  x = 0;
  y = 0;
  w = 240;
  h = 8*GRID_SIZE;
  
  font5 = Text();
  font5.setFont(MAIN_FONT, 5);
  
  
  noiseShader.load("shadersGL3/noise");
  
  t = 0;
  update_x = 0;
  noise_off = ofRandom(100,1000);
  noise_w = w;
  noise_h = 6*GRID_SIZE;
  initTexture(1);
  
  hi_count = 7;
  for (int i = 0; i < hi_count; i++)
    highlights.push_back(ofPoint(0,0));
  selectHighlights();
  
  delay = 0;
  
  tline1.w = w;
  tline1.duration = 40;
  tline1.setDelay(0);
  
  tline2.y = h;
  tline2.w = w;
  tline2.duration = 40;
  tline2.setDelay(0);
  
  initializeText();
  
  initAnimated();
  newEvent(0, 300, 0, true); // intro
  newEvent(0, -1, 1, false); // main
}

void NoiseVisualization::update() {
  if (time+delay > 100 && (int)t % 5 == 0) {
    
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
      selectHighlights();
    }
  }
  
  t += 1;
  Animated::update();
}

void NoiseVisualization::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    /*int index = getCurrentEventIndex();
    animation_event_t e = events[index];
    if (e.id == 0) {*/
      // Intro
      tline1.draw();
      tline2.draw();
      
      // Text
      for (int i = 0; i < texts.size(); i++)
        texts[i].draw();
      
      if (time+delay > 100)
        drawNoise(false);
      
    /*} else if (e.id == 1) {
      // Main
      
      ofSetColor(COLOR_LINE);
      // Top
      tick_line(0, w, 0);
      // Bottom
      tick_line(0, w, h);
      
      ofSetColor(COLOR_135);
      font5.drawString("SYSTEM INSPECTOR", 5, 7);
      ofSetColor(COLOR_55);
      font5.drawStringFromTopRight("INVERSION", w-5, 7);
      font5.drawStringFromTopRight("SYSTEM INSPECTOR", w-5, h-11);
      font5.drawStringFromTopRight("LOAD", w-5, h-18);
      ofSetColor(COLOR_55);
      font5.drawStringFromTopRight("HIGH", w-23, h-18);
     
      drawNoise(false);
    }*/
  }
  ofPopMatrix();
}

void NoiseVisualization::drawNoise(bool showHighlights) {
  displacementTexture.getTextureReference().bind();
  
  ofPushMatrix();
  {
    ofTranslate(0,1*GRID_SIZE);
    ofSetColor(COLOR_95);
    
    if (showHighlights) {
      ofNoFill();
      for (int i = 0; i < hi_count; i++)
        ofRect(highlights[i].x, highlights[i].y, 6, 6);
    }
    
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

void NoiseVisualization::selectHighlights() {
  for (int i = 0; i < hi_count; i++) {
    do {
      highlights[i].x = ofRandom(10,noise_w-10);
      highlights[i].y = ofRandom(10,noise_h-10);
    } while (invalidHighlight(i));
  }
}

bool NoiseVisualization::invalidHighlight(int index) {
  // Return true if index too close to any other highlight up to index-1
  ofPoint p = highlights[index];
  for (int i = 0; i < index; i++) {
    if (abs(p.x-highlights[i].x) < 10)
      return true;
  }
  return false;
}

void NoiseVisualization::setDelay(float delay_) {
  delay = delay_;
  tline1.setDelay(delay);
  tline2.setDelay(delay-5);
  tline1.setEvents(events);
  tline2.setEvents(events);
  initializeText();
}

void NoiseVisualization::initializeText() {
  texts.clear();
  float textDelay = -40;
  // Top Left
  texts.push_back(newText("SYSTEM MAP", 5,
                          5, 7,
                          10, delay+textDelay,
                          COLOR_135,
                          false));
  texts.push_back(newText("NOISE VISUALIZATION", 5,
                          w-5, 7,
                          10, delay+textDelay-5,
                          COLOR_55,
                          true));
  texts.push_back(newText("NORMAL", 5,
                          w-5, h-11,
                          10, delay+textDelay-10,
                          COLOR_55,
                          true));

  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}


