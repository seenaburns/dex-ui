#include "easing-utils.h"

/*
 -----------------------
 EXTERNAL INTERFACE
 -----------------------
 */

float easeLinear(float time, float start, float stop, float dur) {
  float t = time/dur;
  if (time < 0)
    return start;
  if (time > dur)
    return stop;
  
  float eased = computeEaseLinear(t);
//  float eased = cacheEaseLinear(t);
  return rangeMap(eased,start,stop);
}

float easeIn(float time, float start, float stop, float dur) {
  float t = time/dur;
  if (time < 0)
    return start;
  if (time > dur)
    return stop;
  
  float eased = computeEaseIn(t);
//  float eased = cacheEaseIn(t);
  return rangeMap(eased,start,stop);
}

float easeOut(float time, float start, float stop, float dur) {
  float t = time/dur;
  if (time < 0)
    return start;
  if (time > dur)
    return stop;
  
  float eased = computeEaseOut(t);
//  float eased = cacheEaseOut(t);
  return rangeMap(eased,start,stop);
}

float easeInOut(float time, float start, float stop, float dur) {
  float t = time/dur;
  if (time < 0)
    return start;
  if (time > dur)
    return stop;
  
  float eased = computeEaseInOut(t);
//  float eased = cacheEaseInOut(t);
  return rangeMap(eased,start,stop);
}

float easeQuinticInOutBack(float time, float start, float stop, float dur) {
  float t = time/dur;
  if (time < 0)
    return start;
  if (time > dur)
    return stop;
  
  float eased = computeEaseQuinticInOutBack(t);
//  float eased = cacheEaseQuinticInOutBack(t);
  return rangeMap(eased,start,stop);
}

/*
------------------------------------
NONCACHING IMPLEMENTATIONS (COMPUTE)
------------------------------------
*/
float computeEaseLinear(float t) {
  return t;
}

float computeEaseIn(float t) {
  return t*t;
}

float computeEaseOut(float t) {
  return -(t * (t - 2));
}

float computeEaseInOut(float t) {
  if (t < 0.5)
    return 2*t*t;
  return ((-2 * t * t) + (4 * t) - 1);
}

float computeEaseQuinticInOutBack(float t) {
  float ts = t*t;
  float tc = ts*t;
  return (14.0525*tc*ts + -21.5575*ts*ts + -0.689999999999991*tc + 9.195*ts);
}

/*
 ------------------------------------
 UTILITIES
 ------------------------------------
 */
float rangeMap(float x, float start, float end) {
  return start+(end-start)*x;
}

float flicker(float time, float until, float rate) {
  if (time < 0)
    return 1;
  if ((int)time % (int)rate == 0 || time > until)
    return 1;
  return 0;
}
