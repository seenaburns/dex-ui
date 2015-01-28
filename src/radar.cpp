#include "radar.h"

Radar::Radar() {
  debug = false;
  subdivisions = 10;
  point_count = 8;
  thetaRate = 1/150.0;
  axis_length = 220;
  
  x = 100;
  y = 0;
  w = 400;
  h = 400;
  alphaSub = 0;
  
  absolute_center = ofPoint(300,200);
  
  time = 0;
  minTheta = 0;
  maxTheta = 2;
  change_index = 3;
  
  thetaStep = 6.28/point_count;
  index_update_rate = thetaStep / thetaRate;
  
  radialSplineShader.setGeometryInputType(GL_LINES);
	radialSplineShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	radialSplineShader.setGeometryOutputCount(4);
  radialSplineShader.load("shadersGL3/lines.vert", "shadersGL3/radialFade.frag", "shadersGL3/lines.geom");
  axisShader.setGeometryInputType(GL_LINES);
	axisShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	axisShader.setGeometryOutputCount(4);
  axisShader.load("shadersGL3/lines.vert", "shadersGL3/null.frag", "shadersGL3/lines.geom");
//  axisShader.load("shadersGL3/null.vert", "shadersGL3/radialFade.frag");
  
  axisMesh = ofMesh();
  axisMesh.setMode(OF_PRIMITIVE_LINES);
  for (int i = 0; i < axis_length; i += 10) {
    axisMesh.addVertex(ofPoint(i,0));
  }

  init_aframe();
  
  cam = ofEasyCam();
  cam.setTarget(ofVec3f(0,0,0));
  cam.setDistance(600);
  
  if (!debug)
    cam.disableMouseInput();
}

void Radar::update() {
//  if ((int) time % 10 == 0) {
//    update_aframe();
//  }
  
  // Update change, reset once maxTheta loops completely
  if ((int) time % (int)index_update_rate == 0) {
    change_index = (change_index+1)%polar_aframe_points.size();
    update_aframe();
  }
  
  time += 1;
  
  minTheta += thetaRate;
  maxTheta += thetaRate;
  if (minTheta > 2*PI)
    minTheta = 0;
  if (maxTheta > 2*PI+2) {
    maxTheta = 2;
    change_index = 3;
  }
}

void Radar::draw() {
  update();
  
//  ofNoFill();
//  ofSetColor(255);
//  ofRect(x,y,w,h);
//  ofFill();
  cam.begin(ofRectangle(x, y, w, h));
//  ofRect(0,0,w,h);
  ofNoFill();
  ofSetColor(0,255,0);
  
  radialSplineShader.begin();
  radialSplineShader.setUniform1f("thickness", 3.5);
  radialSplineShader.setUniform1f("minTheta", minTheta);
  radialSplineShader.setUniform1f("maxTheta", maxTheta);
  radialSplineShader.setUniform2f("center", absolute_center.x, ofGetHeight()-absolute_center.y);
  radialSplineShader.setUniform1f("alphaSub", alphaSub);
  
  float descale = 0.1;
  for (int i = 0; i < 9; i++) {
    ofPushMatrix();
    {
      ofScale(1-descale*i, 1-descale*i, 1-descale*i);
      bezierLineMesh.draw();
    }
    ofPopMatrix();
  }
  radialSplineShader.end();
  
  // Rotating period
//  axisShader.begin();
//  axisShader.setUniform1f("thickness", 1.0);
  ofSetColor(COLOR_95);
  draw_axis(maxTheta);
  draw_axis(minTheta);
//  axisShader.end();

  if (debug) {
    ofSetColor(255,150);
    debug_draw_bezier_segments();
    debug_draw_aframe();
    
    // Axes
    ofSetColor(255,0,0);
    ofLine(0, 0, 0, 20, 0, 0);
    ofSetColor(0,255,0);
    ofLine(0, 0, 0, 0, 20, 0);
    ofSetColor(0,0,255);
    ofLine(0, 0, 0, 0, 0, 20);
  }
  cam.end();
}

void Radar::set_theta_rate(float tr) {
  thetaRate = tr;
  index_update_rate = thetaStep / thetaRate;
}

void Radar::compute_bezier_from_aframe() {
  // From the aframe points, compute the bezier segments
  // place bezier structs into bezier_segments vector
  bezier_segments.clear();

  ofPoint start = get_next_vertex(-1);
  for (int i = 0; i < aframe_points.size(); i++) {
    ofPoint a1 = get_aframe_point(i);
    ofPoint a2 = get_aframe_point(i+1);
    ofPoint c1 = intermediate_point(a1, a2, 1/3.0);
    ofPoint c2 = intermediate_point(a1, a2, 2/3.0);
    ofPoint end = get_next_vertex(i);
    
    bezier b = bezier();
    b.start = start;
    b.c1 = c1;
    b.c2 = c2;
    b.end = end;
    
    bezier_segments.push_back(b);
    
    start = end;
  }
}

void Radar::compute_lines_from_bezier() {
  // From the bezier_segments, subdivide the bezier to create line segments
  // Place line segments in bezierLineMesh
  bezierLineMesh = ofMesh();
  bezierLineMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
  
  float t_step = 1/subdivisions;
  
  for (int i = 0; i < bezier_segments.size(); i++) {
    bezier b = bezier_segments[i];
    vector<ofPoint> points = bezier_to_points(b);
    for (float t = 0; t <= 1; t+= t_step) {
      ofPoint p = rec_de_casteljau(points, t);
      bezierLineMesh.addVertex(p);
    }
  }
  // Connect end and start
  bezierLineMesh.addVertex(bezier_segments[0].start);
}


ofPoint Radar::get_aframe_point(int i) {
  int modi = i%aframe_points.size();
  if (i < 0)
    modi = aframe_points.size()+i;
  return aframe_points[modi];
}

ofPoint Radar::get_next_vertex(int i) {
  ofPoint a1 = get_aframe_point(i);
  ofPoint a2 = get_aframe_point(i+1);
  ofPoint a3 = get_aframe_point(i+2);
  ofPoint p1 = intermediate_point(a1, a2, 2/3.0);
  ofPoint p2 = intermediate_point(a2, a3, 1/3.0);
  return intermediate_point(p1,p2,0.5);
}

void Radar::init_aframe() {
  // Initialize aframe (both polar/normal points)
  for (int i = 0; i < point_count; i++) {
    float theta = i * thetaStep;
    float phi = ofRandom(PI);
    phi = clamp(phi, PI/3, 2*PI/3);
    polar_point pp = polar_point();
    pp.r = 200;
    pp.theta = theta;
    pp.phi = phi;
    polar_aframe_points.push_back(pp);
    aframe_points.push_back(polar_to_cartesian(pp.r, pp.theta, pp.phi));
  }
}

void Radar::update_aframe() {
  polar_point pp = polar_aframe_points[change_index];
  float phi_change = ofRandom(2)-1;
  pp.phi += phi_change;
  pp.phi = clamp(pp.phi, PI/3, PI);
  polar_aframe_points.at(change_index) = pp;
  
  ofPoint p = polar_to_cartesian(pp.r, pp.theta, pp.phi);
  aframe_points.at(change_index) = p;
  
  compute_bezier_from_aframe();
  compute_lines_from_bezier();
}

void Radar::draw_axis(float rotation) {
  ofPushMatrix();
  {
    ofRotateZ(rotation/(2*PI)*360);
    axisMesh.draw();
    ofNoFill();
    ofRect(axis_length, -3, 6, 6);
  }
  ofPopMatrix();
}

void Radar::debug_draw_bezier_segments() {
  ofNoFill();
  ofBeginShape();
  {
    for (int i = 0; i < bezier_segments.size(); i++) {
      bezier b = bezier_segments[i];
      if (i == 0)
        ofVertex(b.start);
      ofBezierVertex(b.c1, b.c2, b.end);
    }
  }
  ofEndShape();
}

void Radar::debug_draw_aframe() {
  ofFill();
  for (int i = 0; i < aframe_points.size(); i++) {
    ofPoint p = aframe_points[i];
    ofRect(p, 3, 3);
    polar_point pp = polar_aframe_points[i];
    ofDrawBitmapString(ofToString(pp.theta), p);
  }
}

//
// UTILITY FUNCTIONS
//
ofPoint intermediate_point(ofPoint p1, ofPoint p2, float percent) {
  // Find point at percent along from p1 to p2
  return p1 + (p2-p1)*percent;
}

ofPoint rec_de_casteljau(vector<ofPoint> points, float t) {
  // Recursively compute the point at t=... on a bezier curve (defined by
  // the 4 points in the 'points' vector) using the de casteljau algorithm
  //
  // Essentially this means if t=0.1 find the point 10% along the bezier.
  //
  if (points.size() == 1)
    return points[0];
  
  vector<ofPoint> intermediates;
  for (int i = 0; i < points.size()-1; i++) {
    ofPoint p1 = points[i];
    ofPoint p2 = points[i+1];
    ofPoint p = intermediate_point(p1, p2, t);
    intermediates.push_back(p);
  }
  
  return rec_de_casteljau(intermediates, t);
}

ofPoint polar_to_cartesian(float radius, float theta, float phi) {
  // Convert from spherical polar coordinates and cartesian coordinates
  float x = radius * cos(theta) * sin(phi);
  float y = radius * sin(theta) * sin(phi);
  float z = radius * cos(phi);
  return ofPoint(x,y,z);
}

vector<ofPoint> bezier_to_points(bezier b) {
  // Convert bezier struct to point vector
  vector<ofPoint> points;
  points.push_back(b.start);
  points.push_back(b.c1);
  points.push_back(b.c2);
  points.push_back(b.end);
  return points;
}

float clamp(float in, float min, float max) {
  if (in < min) return min;
  if (in > max) return max;
  return in;
}
