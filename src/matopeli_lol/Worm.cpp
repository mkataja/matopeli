#include "Worm.h"
#include "WormPart.h"
#include "Apple.h"

#define WALL_COLLISIONS true
#define WORM_COLLISIONS true

class WormPart parts[64];

void Worm::init() {
  dead = false;
  head_index = 1;
  tail_index = 0;
  xspeed = 1;
  yspeed = 0;
  parts[head_index].x = 1;
  parts[head_index].y = 3;
  parts[tail_index].x = 0;
  parts[tail_index].y = 3;
  for (int i = 0; i < 64; i++) {
    parts[i].blinkstate = false;
  }
}

int Worm::getHeadX() {
  return parts[head_index].x;
}

int Worm::getHeadY() {
  return parts[head_index].y;
}

bool Worm::move(int xinput, int yinput) {
  if (xspeed) {
    if (yinput) {
      xspeed = 0;
      yspeed = yinput;
    }
  }
  else if (yspeed) {
    if (xinput) {
      yspeed = 0;
      xspeed = xinput;
    }
  }
  int newx = parts[head_index].x + xspeed;
  int newy = parts[head_index].y + yspeed;
  
  if (WALL_COLLISIONS) {
    if (newx < 0 || newx > 7 || newy <0 || newy > 7) {
      dead = true;
    }
  }
  else {
    // No wall collisions: wrap the worm around
    if (newx > 7) {
      newx = 0;
    }
    if (newx < 0) {
      newx = 7;
    }
    if (newy > 7) {
      newy = 0;
    }
    if (newy < 0) {
      newy = 7;
    }
  }
  
  if (WORM_COLLISIONS) {
    if (cellReserved(newx, newy)) {
      dead = true;
    }
  }

  if (dead) {
    return false;
  } 
  else {
    head_index++;
    head_index = head_index % 64;
    parts[head_index].x = newx;
    parts[head_index].y = newy;

    tail_index++;
    tail_index = tail_index % 64;
    return true;
  }
}

void Worm::grow() {
  tail_index--;
  if (tail_index == -1) {
    tail_index = 63;
  }
}

void Worm::draw(Frame* frame) {
  int i = tail_index;
  do {
    if (!dead)
      parts[i%64].draw(frame);
    else
      parts[i%64].drawDead(frame);
    i++;
  } 
  while(i%64 != (head_index + 1) % 64);
}

bool Worm::cellReserved(int x, int y) {
  int i = tail_index;
  do {
    if (parts[i].x == x && parts[i].y == y)
      return true;
    i++;
  } 
  while(i%64 != (head_index + 1) % 64);
  return false;
}


