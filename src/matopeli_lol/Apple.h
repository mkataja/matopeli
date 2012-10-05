#ifndef __APPLE_INCLUDED__
#define __APPLE_INCLUDED__

class Frame;
class Worm;

class Apple {
private:
  int x;
  int y;

public:
  void add(Worm* worm);
  bool eat(Worm* worm);
  void draw(Frame* frame);
};

#endif
