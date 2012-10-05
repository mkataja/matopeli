#ifndef __FRAME_INCLUDED__
#define __FRAME_INCLUDED__

class Frame{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO

public:
  unsigned char r[8][8];
  unsigned char g[8][8];
  unsigned char b[8][8];

  void setPixel(int x, int y, unsigned char r_val, unsigned char g_val, unsigned char b_val);
  void clear();
};

#endif
