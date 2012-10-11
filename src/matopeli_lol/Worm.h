#ifndef __WORM_INCLUDED__
#define __WORM_INCLUDED__

class Frame;

class Worm{
private:
  int head_index, tail_index;
  int xspeed, yspeed;
  bool dead;

public:
  void init();
  bool move(int xinput, int yinput);
  void grow();
  void draw(Frame* frame);
  bool cellReserved(int x, int y);
  int getHeadX();
  int getHeadY();
};

#endif
