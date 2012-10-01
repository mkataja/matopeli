#include <new.h>
#include <EasyTransfer.h>

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

class WormPart{
  public:
  int x;
  int y;
  WormPart* next;
  
  WormPart(int x, int y, WormPart* next) {
    x = x;
    y = y;
    next = next;
  }
  
  void draw() {
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    frame.g[x][y] = 255;
    return;
    if (next) {
      next->draw();
    }
  }
};

class Worm{
  WormPart* head;
  int xspeed;
  int yspeed;
  
  public:
  Worm(int x, int y, int xspeed, int yspeed) {
    xspeed = xspeed;
    yspeed = yspeed;
    head = new WormPart(x, y, NULL);
  }
  
  boolean move() {
    int newx = head->x + xspeed;
    int newy = head->y + yspeed;
    
    if (newx < 0 || newx > 7 || newy <0 || newy > 7) {
      //return false;
    }
    
    WormPart* temp = head;
    while (temp->next) {
      if (newx == temp->x && newy == temp->y) {
        return false;
      }
      if (!temp->next->next) {
        delete temp->next;
        temp->next = NULL;
      }
      temp = temp->next;
    }
    
    head = new WormPart(newx, newy, head);
  }
  
  void draw() {
    head->draw();
  }
};

void setup(){
  Serial.begin(19200);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(frame), &Serial);

  pinMode(13, OUTPUT);

  randomSeed(analogRead(0));
}

boolean lol = false;

void loop(){
  Worm* worm = new Worm(3, 3, 1, 0);
  //worm->move();
  worm->draw();
  
  if (lol) {
    frame.g[0][0] = 0;
  } else {
    frame.g[0][0] = 255;    
  }
  lol = !lol;
  //ET.sendData();
  delay(500);
}



