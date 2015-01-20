#pragma once
#include "ofMain.h"

/*
 -----------------------
 EXTERNAL INTERFACE
 -----------------------
 time: time counter, easing will run from 0 -> dur
 start: starting value
 stop: ending value
 dur: length of easing (from 0)
 */
float easeLinear(float time, float start, float stop, float dur);
float easeIn(float time, float start, float stop, float dur);
float easeOut(float time, float start, float stop, float dur);
float easeInOut(float time, float start, float stop, float dur);
float easeQuinticInOutBack(float time, float start, float stop, float dur);

/*
 -----------------------
 CACHING IMPLEMENTATIONS
 -----------------------
 cheaply caching by using an array, index = (int) float*CACHE_SIZE, e.g. 1000 offers 3 digits of specificity
 t: time from 0 to 1, easing starts at 0 ends at 1
 return 0 - 1 float, out back may overshoot
*/

/*
 ------------------------------------
 NONCACHING IMPLEMENTATIONS (COMPUTE)
 ------------------------------------
 t: time from 0 to 1, easing starts at 0 ends at 1
 return 0 - 1 float, out back may overshoot
*/
float computeEaseLinear(float t);
float computeEaseIn(float t);
float computeEaseOut(float t);
float computeEaseInOut(float t);
float computeEaseQuinticInOutBack(float t);

/*
 ------------------------------------
 UTILITIES
 ------------------------------------
*/
// Map x (in range 0->1, to range start->end
float rangeMap(float x, float start, float end);

// Flicker
float flicker(float time, float until, float rate);