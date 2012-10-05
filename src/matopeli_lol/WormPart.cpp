#include "WormPart.h"
#include "Apple.h"
#include "Frame.h"

void WormPart::draw(Frame* frame) {
  frame->setPixel(x, y, 255, 100, 100);
}

void WormPart::drawDead(Frame* frame) {
  blinkstate = !blinkstate;
  if (blinkstate) {
    frame->setPixel(x, y, 255, 0, 0);
  }
  else {
    frame->setPixel(x, y, 0, 0, 0);
  }
}
