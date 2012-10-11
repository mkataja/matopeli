#include <EasyTransfer.h>

#include "Frame.h"
#include "Worm.h"
#include "Apple.h"

Frame frame;
Worm worm;
Apple apple;

#define JOYSTICK_DEAD_ZONE 100
#define JOYSTICK_CENTER 512

//create object
EasyTransfer ET;

void drawScene() {
  worm.draw(&frame);
  apple.draw(&frame);
  ET.sendData();
  frame.clear();
}

void setup(){
  Serial.begin(19200);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(frame), &Serial);

  pinMode(13, OUTPUT);

  randomSeed(analogRead(3));

  worm.init();
  apple.add(&worm);
  drawScene();
}

long previousMillis = 0;
long interval = 300;
int xinput = 0;
int yinput = 0;

void loop(){
  int x = analogRead(0) - JOYSTICK_CENTER;
  int y = analogRead(1) - JOYSTICK_CENTER;
  if (abs(x) - JOYSTICK_DEAD_ZONE > 0 || abs(y) - JOYSTICK_DEAD_ZONE > 0) {
    if (abs(x) > abs(y)) {
      yinput = 0;
      if (x < 0 - JOYSTICK_DEAD_ZONE) {
        xinput = -1;
      }
      if (x > 0 - JOYSTICK_DEAD_ZONE) {
        xinput = 1;
      }
    } 
    else {
      xinput = 0;
      if (y < 0 - JOYSTICK_DEAD_ZONE) {
        yinput = 1;
      }
      if (y > 0 - JOYSTICK_DEAD_ZONE) {
        yinput = -1;
      }
    }
  }

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;  

    // Move and draw the worm
    boolean alive = worm.move(xinput, yinput);
    xinput = 0;
    yinput = 0;
    if (!alive) {
      static int respawn = 10;
      respawn--;
      if (respawn == 0) {
        worm.init();
        apple.add(&worm);
        respawn = 10;
      }
    }

    if (apple.eat(&worm)) {
      worm.grow();
    }

    drawScene();
  }
}

