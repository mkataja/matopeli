#ifndef __WORMPART_INCLUDED__
#define __WORMPART_INCLUDED__

class Frame;

class WormPart{
public:
  int x;
  int y;
  bool blinkstate;

  void draw(Frame* frame);
  void drawDead(Frame* frame);
};

#endif
