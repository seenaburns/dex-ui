#include "text.h"

Text::Text() {
  
}

void Text::setFont(string font, int size) {
  ofFont.loadFont(font, size, true, true);
}

void Text::drawString(string s, float x, float y) {
  ofRectangle bounds = ofFont.getStringBoundingBox(s, x, y);
  ofFont.drawString(s, x, y+bounds.height);
}

void Text::drawStringFromTopRight(string s, float x, float y) {
  ofRectangle bounds = ofFont.getStringBoundingBox(s, x, y);
  ofFont.drawString(s, x-bounds.width, y+bounds.height);
}