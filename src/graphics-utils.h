/*

  graphics-utils.h

  Any accessory graphics functions.

*/
#pragma once
#include "ofMain.h"

#define GRID_SIZE 15
#define WIDTH 1920
#define HEIGHT 1200

#define TICK_SIZE 2

// Colors
#define COLOR_15    ofColor::fromHex(0x0D100E)
#define COLOR_35    ofColor::fromHex(0x202924)
#define COLOR_55    ofColor::fromHex(0x2F3C35)
#define COLOR_75    ofColor::fromHex(0x3a4a41)
#define COLOR_95    ofColor::fromHex(0x52685C)
//#define COLOR_135   ofColor::fromHex(0x779283)
#define COLOR_135   ofColor::fromHex(0x768b7d)
//#define COLOR_175   ofColor::fromHex(0x52685C)
#define COLOR_175   ofColor::fromHex(0x9baaa0)
#define COLOR_LINE COLOR_55

#define MAIN_FONT_LINUX ""
#define MAIN_FONT_MAC ""
#define MAIN_FONT MAIN_FONT_LINUX

#define TERMINAL_FONT_LINUX ""
#define TERMINAL_FONT TERMINAL_FONT_LINUX

#define NOISE_BG "images/noise-bg-color-darker.png"

void tick_line(float x1, float x2, float y);
void tick(float x, float y);
