#pragma once
#include "ofMain.h"
#include <vector>
#include "graphics-utils.h"

//
// DATA STRUCTURES
//
struct bezier {
  ofPoint start;
  ofPoint c1;
  ofPoint c2;
  ofPoint end;
};

struct line {
  ofPoint start;
  ofPoint end;
};

struct polar_point {
  float r;
  float theta;
  float phi;
};

//
// UTILITY FUNCTIONS
//
ofPoint intermediate_point(ofPoint p1, ofPoint p2, float percent);
ofPoint rec_de_casteljau(vector<ofPoint> points, float t);
ofPoint polar_to_cartesian(float radius, float theta, float phi);
vector<ofPoint> bezier_to_points(bezier b);
float clamp(float in, float min, float max);

class Radar {
public:
  Radar();
  void update();
  void draw();
  void set_theta_rate(float tr);
  
  float x;
  float y;
  float w;
  float h;
  float minTheta;
  float maxTheta;
  float alphaSub;
  
  ofPoint absolute_center;
  ofEasyCam cam;
  
  bool debug;

private:
  // Variables and objects
  std::vector<polar_point> polar_aframe_points;
  std::vector<ofPoint> aframe_points;
  // To be continuous, end of bezier/line 1 = start of bezier/line 2
  std::vector<bezier> bezier_segments;
  ofMesh bezierLineMesh;
  float subdivisions;
  float time;
  
  float point_count;
  float axis_length;
  
  float thetaRate;
  float thetaStep;
  
  float index_update_rate;
  
  int change_index;
  
  ofShader radialSplineShader;
  ofShader axisShader;
  
  ofMesh axisMesh;
  
  // Main functionality
  void init_aframe();
  void update_aframe();
  void compute_bezier_from_aframe();
  void compute_lines_from_bezier();
  
  void draw_axis(float rotation);
  
  // Utility
  ofPoint get_aframe_point(int i);
  ofPoint get_next_vertex(int i);
  void update_change_index();
  
  // Debug
  void debug_draw_bezier_segments();
  void debug_draw_aframe();
};