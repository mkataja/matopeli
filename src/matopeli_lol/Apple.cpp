#include "Apple.h"
#include <Arduino.h>
#include "Worm.h"
#include "Frame.h"

void Apple::add(Worm* worm) {
  do {
    x = random(0, 7);
    y = random(0, 7);
  } 
  while (worm->cellReserved(x, y));
}

bool Apple::eat(Worm* worm) {
  if (worm->getHeadX() == x && worm->getHeadY() == y) {
    add(worm);
    return true;
  }
  else {
    return false;
  }
}

void Apple::draw(Frame* frame) {
  frame->setPixel(x, y, 0, 255, 0);
}
