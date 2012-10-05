#include "Frame.h"

void Frame::setPixel(int x, int y, unsigned char r_val, unsigned char g_val, unsigned char b_val) {
  r[y][x] = r_val;
  g[y][x] = g_val;
  b[y][x] = b_val;
}

void Frame::clear() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      r[x][y] = 0;
      g[x][y] = 0;
      b[x][y] = 0;
    }
  }
}

