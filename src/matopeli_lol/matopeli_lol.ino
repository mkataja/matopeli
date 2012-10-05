#include <EasyTransfer.h>

#include "Frame.h"
#include "Worm.h"
#include "Apple.h"

Frame frame;
Worm worm;
Apple apple;

#define JOYSTICK_DEAD_ZONE 200
#define JOYSTICK_CENTER 512

//create object
EasyTransfer ET;

void setup(){
  Serial.begin(19200);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(frame), &Serial);

  pinMode(13, OUTPUT);

  randomSeed(analogRead(3));

  worm.init();
  apple.add(&worm);
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
  boolean alive = worm.move(xinput, yinput);
  if (!alive) {
    static int respawn = 10;
    respawn--;
    if (respawn == 0) {
      worm.respawn();
      respawn = 10;
    }
  }

  if (apple.eat(&worm)) {
    worm.grow();
  }

  worm.draw(&frame);
  apple.draw(&frame);
  ET.sendData();
  frame.clear();
  delay(300);
}










