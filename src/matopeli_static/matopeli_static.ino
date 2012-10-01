#include <EasyTransfer.h>

#define JOYSTICK_DEAD_ZONE 200
#define JOYSTICK_CENTER 512

//create object
EasyTransfer ET;

struct Frame{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  unsigned char r[8][8];
  unsigned char g[8][8];
  unsigned char b[8][8];
};

Frame frame;

void clearFrame() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      frame.r[x][y] = 0;
      frame.g[x][y] = 0;
      frame.b[x][y] = 0;
    }
  }
}

class WormPart{
public:
  int x;
  int y;

  void draw() {
    frame.r[y][x] = 255;
    frame.g[y][x] = 100;
    frame.b[y][x] = 100;
  }
} 
parts[64];

class Worm{
public:
  int head_index, tail_index;
  int xspeed, yspeed;

  void init() {
    head_index = 1;
    tail_index = 0;
    xspeed = 1;
    yspeed = 0;
    parts[head_index].x = 1;
    parts[head_index].y = 3;
    parts[tail_index].x = 0;
    parts[tail_index].y = 3;
  }

  boolean move(int xinput, int yinput) {
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
    if (newx < 0 || newx > 7 || newy <0 || newy > 7) {
      // Wall collision detection disabled:
      //return false;
    }
    newx = newx % 8;
    newy = newy % 8;
    head_index++;
    head_index = head_index % 64;
    tail_index++;
    tail_index = tail_index % 64;
    parts[head_index].x = newx;
    parts[head_index].y = newy;
  }

  void draw() {
    int i = tail_index;
    do {
      parts[i%64].draw();
      i++;
    } 
    while(i%64 != (head_index + 1) % 64);
  }
} 
worm;

void setup(){
  Serial.begin(19200);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(frame), &Serial);

  pinMode(13, OUTPUT);

  randomSeed(analogRead(0));

  worm.init();
}

void loop(){
  int xinput = 0;
  int yinput = 0;
  if (analogRead(0) - JOYSTICK_CENTER < 0 - JOYSTICK_DEAD_ZONE) {
    xinput = -1;
  }
  if (analogRead(0) - JOYSTICK_CENTER > 0 + JOYSTICK_DEAD_ZONE) {
    xinput = 1;
  }
  if (analogRead(1) - JOYSTICK_CENTER < 0 - JOYSTICK_DEAD_ZONE) {
    yinput = 1;
  }
  if (analogRead(1) - JOYSTICK_CENTER > 0 + JOYSTICK_DEAD_ZONE) {
    yinput = -1;
  }
  worm.move(xinput, yinput);
  worm.draw();
  ET.sendData();
  clearFrame();
  delay(500);
}



