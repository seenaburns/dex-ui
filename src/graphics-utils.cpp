#include "graphics-utils.h"

// Draw horizontal line from x1 to x2 at height y, with ticks at end
// Handles half pixel adjustment
void tick_line(float x1, float x2, float y) {
  // Pixel adjust
  x1 -= 0.5;
  x2 += 0.5;
  y += 0.5;

  ofLine(x1, y, x2, y);
  tick(x1, y);
  tick(x2, y);
}

// Draw vertical tick at x,y, of height 2*TICK_SIZE
// DOES NOT half pixel adjust
void tick(float x, float y) {
  ofLine(x, y-TICK_SIZE, x, y+TICK_SIZE);
}
