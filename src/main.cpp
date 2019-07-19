#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "PinNames.h"
#include <pickup.h>
#include <sensors.h>
#include <Servo.h>
#include <claw.h>

#define LED_PIN PB14
#define SONAR_ECHO PA7
#define SONAR_TRIG PA6

#define PING 0
#define PICKUP 1
#define PUTDOWN 2


float armHeight = 0.0;
float armLength = 0.0;
bool clawSuccess = 0.0;
float armAngle = 0.0;

int state = GOING_TO_MAX;

int doneYet = 0;

Servo clawServo;

volatile byte x = 1;
void receiveEvent(int numBytes);

void receiveEvent(int numBytes) {
  int receiveBuffer [BUFFER_SIZE];
  int receivedBytes = 0;
  int direction = 0;
  int postDistance = 0;

  // are you done the task
  // 0 : not done yet
  // 1 : done successfully
  // 2 : I could not do it
  
  while (Wire.available() && receivedBytes < BUFFER_SIZE){
    receiveBuffer[receivedBytes] = Wire.read();
    receivedBytes ++;
  }
  digitalWrite(LED_PIN, LOW);
  Serial.print("received bytes: ");
  Serial.print(String(receiveBuffer[0]));
  Serial.println (String(receiveBuffer[1]));
  digitalWrite(LED_PIN, HIGH);
  int action = receiveBuffer[0];
  switch(action) {
    case PING:
      //ping back
      break;
    case PICKUP:
      direction = receiveBuffer[1];
      postDistance = receiveBuffer[2];
      state = GOING_TO_MAX;
      doneYet = pickupMode(direction , postDistance);
      //pick up the stone
      break;
    case PUTDOWN:
      //put it down
      break;
  }
  Wire.write(doneYet); // CHANGE
}

void requestEvent() {
  // DO NOT USE A DELAY IN THIS FUNCTION
  Serial.println("Slave: REQUESTED");
  Wire.write(doneYet);
  Serial.println("Slave: replied");
}

void setup() {
  Serial.begin(9600);
  delay(5000);
  pinMode(PICKUP_SWITCH, INPUT);
  clawServo.attach(SERVO_PIN);
  Wire.begin(BPILL_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.println("setup");
  Serial.println("Setup complete");
}

void loop() {

}