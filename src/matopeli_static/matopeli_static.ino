#include <EasyTransfer.h>

#define JOYSTICK_DEAD_ZONE 200
#define JOYSTICK_CENTER 512
#define WALL_COLLISIONS true

//create object
EasyTransfer ET;

struct Frame{
  //put your variable definitions here for the data you want to receive
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  unsigned char r[8][8];
  unsigned char g[8][8];
  unsigned char b[8][8];

  void clear() {
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        r[x][y] = 0;
        g[x][y] = 0;
        b[x][y] = 0;
      }
    }
  }
};

Frame frame;

class WormPart{
public:
  int x;
  int y;
  boolean blinkstate;

  void draw() {
    frame.r[y][x] = 255;
    frame.g[y][x] = 100;
    frame.b[y][x] = 100;
  }

  void drawDead() {
    blinkstate = !blinkstate;
    if (blinkstate) {
      frame.r[y][x] = 255;
    }
    else {
      frame.r[y][x] = 0;
    }
  }
} 
parts[64];

class Worm{
private:
  int head_index, tail_index;
  int xspeed, yspeed;
  boolean dead;

public:
  void init() {
    dead = false;
    head_index = 1;
    tail_index = 0;
    xspeed = 1;
    yspeed = 0;
    parts[head_index].x = 1;
    parts[head_index].y = 3;
    parts[tail_index].x = 0;
    parts[tail_index].y = 3;
  }

  void respawn() {
    init();
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
    if (WALL_COLLISIONS) {
      if (newx < 0 || newx > 7 || newy <0 || newy > 7) {
        dead = true;
      }
    }
    else {
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

    if (dead) {
      return false;
    } 
    else {
      head_index++;
      head_index = head_index % 64;
      tail_index++;
      tail_index = tail_index % 64;
      parts[head_index].x = newx;
      parts[head_index].y = newy;
      return true;
    }
  }

  void draw() {
    int i = tail_index;
    do {
      if (!dead)
        parts[i%64].draw();
      else
        parts[i%64].drawDead();
      i++;
    } 
    while(i%64 != (head_index + 1) % 64);
  }

  boolean cellReserved(int x, int y) {
    int i = tail_index;
    do {
      if (parts[i].x == x && parts[i].y == y)
        return true;
      i++;
    } 
    while(i%64 != (head_index + 1) % 64);
    return false;
  }
} 
worm;

class Apple {
private:
  int x;
  int y;

public:
  void add() {
    do {
      x = random(0, 7);
      y = random(0, 7);
    } 
    while (worm.cellReserved(x, y));
  }

  boolean eat(int headx, int heady) {
    if (headx == x && heady == y) {
      add();
      return true;
    }
    else {
      return false;
    }
  }

  void draw() {
    frame.g[y][x] = 255;
  }
} 
apple;

void setup(){
  Serial.begin(19200);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(frame), &Serial);

  pinMode(13, OUTPUT);

  randomSeed(analogRead(0));

  worm.init();
  apple.add();
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
  boolean dead = worm.move(xinput, yinput);
  if (dead) {
    static int respawn = 10;
    respawn--;
    if (respawn == 0) {
      worm.respawn();
    }
  }
  worm.draw();
  apple.draw();
  ET.sendData();
  frame.clear();
  delay(300);
}





