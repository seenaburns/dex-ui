#include "graph.h"
#include "graphics-utils.h"
#include "easing-utils.h"

Graph::Graph() {
  x = 0;
  y = 0;
  w = 240;
  h = 2*GRID_SIZE;
  
  show_rect1 = false;
  show_rect2 = false;
  show_rect3 = false;
  
  float graph_w = 13 * GRID_SIZE-5;
  anchor_count = 13*3;
  anchor_xoff = graph_w/anchor_count;
  anchor_yoff = 12;
  for (int i = 0; i < anchor_count; i++) {
    ofPoint newP = ofPoint(i*anchor_xoff, 0);
    aframe_points.push_back(newP);
  }
  
  t = 0;
  
  delay = 0;
  introLinesDur = ofRandom(25)+25;
  
  // Init texts
  texts.push_back(newText("", 5,
                          0, -1,
                          10, 0,
                          COLOR_135,
                          false));
  texts.push_back(newText("L", 5,
                          0, h-4,
                          10, 0,
                          COLOR_55,
                          false));
  texts.push_back(newText("M", 5,
                          15, h-4,
                          10, 0,
                          COLOR_55,
                          false));
  texts.push_back(newText("H", 5,
                          32, h-4,
                          10, 0,
                          COLOR_55,
                          false));
  
  // Animation settings
  events.clear();
  newEvent(0, 300, 0, 1); // intro
  newEvent(0, -1, 1, 1); // main
  currentEvent = events[0];
  
  updateDependencyEvents();
  updateDependencyDelays(getDelay());
}

void Graph::update() {
  // Retest right side rects
  if ((int)t % 60 == 0) {
    show_rect1 = ofRandom(0,1) > 0.5;
    show_rect2 = ofRandom(0,1) > 0.5;
    show_rect3 = ofRandom(0,1) > 0.5;
  }
  
  // ONLY UPDATE SPLINE IF NOT INTRO
  if (currentEvent.id != 0) {
    // Update goals every n frames
    int n = 50;
    if ((int)t % n == 0) {
      
      for (int i = 1; i < aframe_points.size()-1; i++) {
        aframe_points[i].y = aframe_points[i+1].y;
        aframe_points[i].x = i*anchor_xoff;
      }
      aframe_points[aframe_points.size()-1].x = (aframe_points.size()-2)*anchor_xoff;
      
      new_sample = ofRandom(-1,1) * anchor_yoff;
    }
    
    aframe_points[0].y = ofLerp(aframe_points[0].y, aframe_points[1].y, 1.0/n*2);
    aframe_points[aframe_points.size()-1].y = ofLerp(aframe_points[aframe_points.size()-1].y, new_sample, 1.0/n*2);
    for (int i = 1; i < aframe_points.size()-1; i++)
      aframe_points[i].x -= anchor_xoff/n;
  }
  t += 1;
  
  updateTime();
}

void Graph::draw() {
  update();
  ofPushMatrix();
  {
    ofTranslate(x, y);
    
    if (currentEvent.id == 0) {
      // Intro
      // Graph top/bottom lines
      ofSetColor(COLOR_95, 100);
      float tempW = easeInOut(time+delay, 0,  w-4*GRID_SIZE, introLinesDur);
      ofLine(w-1*GRID_SIZE, 0.5, w-1*GRID_SIZE-tempW, 0.5);
      ofLine(w-1*GRID_SIZE, h+0.5, w-1*GRID_SIZE-tempW, h+0.5);
      
      // Actual line
      ofSetColor(COLOR_135);
      tempW = easeInOut(time+delay, 0,  w-4*GRID_SIZE, introLinesDur*1.5);
      ofLine(w-1*GRID_SIZE, h/2, w-1*GRID_SIZE-tempW, h/2);

      // Text
      for (int i = 0; i < texts.size(); i++)
        texts[i].draw();
      
      // Rects on right
      int rect_w = 1;
      ofSetColor(COLOR_75);
      if ((time+delay > 100 && time+delay < 170) || (time+delay > 150 && show_rect1))
        ofRect(w-rect_w+0.5,0,rect_w,7);
      if ((time+delay > 105 && time+delay < 180) || (time+delay > 160 && show_rect1))
        ofRect(w-rect_w+0.5,12,rect_w,7);
      if ((time+delay > 110 && time+delay < 190) || (time+delay > 170 && show_rect1))
        ofRect(w-rect_w+0.5,23,rect_w,7);
      
    } else if (currentEvent.id == 1) {
      // Main
      // Text
      for (int i = 0; i < texts.size(); i++)
        texts[i].draw();

      // Graph top/bottom lines
      ofSetColor(COLOR_95, 100);
      ofLine(3*GRID_SIZE, 0.5, w-1*GRID_SIZE, 0.5);
      ofLine(3*GRID_SIZE, h+0.5, w-1*GRID_SIZE, h+0.5);
      
      // Rects on right
      int rect_w = 1;
      ofSetColor(COLOR_75);
      if (show_rect1)
        ofRect(w-rect_w+0.5,0,rect_w,7);
      if (show_rect2)
        ofRect(w-rect_w+0.5,12,rect_w,7);
      if (show_rect3)
        ofRect(w-rect_w+0.5,23,rect_w,7);
      
      
      // Draw spline
      ofPushMatrix();
      {
        ofTranslate(45,15);
        
        ofNoFill();
        ofSetColor(COLOR_135);
        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofBeginShape();
        {
          ofVertex(aframe_points[0].x,aframe_points[0].y);
          for (int i = 1; i < aframe_points.size()-1; i++) {
            bezier_vertex_from_aframe(aframe_points[i-1], aframe_points[i], aframe_points[i+1]);
          }
          
          ofPoint a1 = aframe_points[aframe_points.size()-2];
          ofPoint a2 = aframe_points[aframe_points.size()-1];
          ofBezierVertex(intermediate_point(a1,a2,1/3.0),
                         intermediate_point(a1,a2,2/3.0),
                         a2);
        }
        ofEndShape();
      }
      ofPopMatrix();
    }
    
  }
  ofPopMatrix();
}

void Graph::setPos(float x_, float y_) {
  x = x_;
  y = y_;
}

void Graph::bezier_vertex_from_aframe(ofPoint aframe_p1, ofPoint aframe_p2, ofPoint aframe_p3) {
  // Compute aframe1 -> aframe2, intermediates at 1/3, 2/3 (anchor1,anchor2)
  // Compute aframe2 -> aframe3, intermediate at 1/3
  // 1/2 between 2/3s intermediate of 1->2, and 1/3 of 2->3 is actual vertex pos
  ofPoint anchor1 = intermediate_point(aframe_p1, aframe_p2, 1/3.0);
  ofPoint anchor2 = intermediate_point(aframe_p1, aframe_p2, 2/3.0);
  ofPoint anchor3 = intermediate_point(aframe_p2, aframe_p3, 1/3.0);
  ofPoint vertex = intermediate_point(anchor2, anchor3, 1/2.0);
  ofBezierVertex(anchor1, anchor2, vertex);
}

ofPoint Graph::intermediate_point(ofPoint p1, ofPoint p2, float distance) {
  return ofPoint((p2.x-p1.x)*distance+p1.x, (p2.y-p1.y)*distance+p1.y);
}

void Graph::setName(string name_) {
  texts[0].s = name_;
}

void Graph::updateDependencyDelays(int delay_) {
  delay = delay_;
  int textDelay = -introLinesDur-5;
  int textDelays[4] = {0,-5,-10,-10};
  for (int i = 0; i < texts.size(); i++)
    texts[i].setDelay(delay_+textDelay+textDelays[i]);
}

void Graph::updateDependencyEvents() {
  for (int i = 0; i < texts.size(); i++)
    texts[i].setEvents(events);
}
