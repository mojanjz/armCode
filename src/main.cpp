#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "PinNames.h"
#include <pickup.h>
#include <sensors.h>
#include <Servo.h>
#include <claw.h>

#define SONAR_ECHO PA7
#define SONAR_TRIG PA6
#define LED_PIN PB14

#define PING 1
#define PICKUP 2
#define PUTDOWN 3
#define BPILL_ADDRESS 69
#define BUFFER_SIZE 3


float armHeight = 0.0;
float armLength = 0.0;
bool clawSuccess = 0.0;
float armAngle = 0.0;

int state = GOING_TO_MAX;
int action;//CHANGE
int direction;
int postDistance;

Servo clawServo;

volatile byte x = 1;
int counter = 0;
byte doneYet = 0;

void receiveEvent(int);
void requestEvent(int);

void receiveEvent(int numBytes) {
  Serial.println("I've received something");
  byte receiveBuffer [BUFFER_SIZE];// CHANGE
  int receivedBytes = 0;
  direction = 0;
  postDistance = 0;

  // are you done the task
  // 0 : not done yet
  // 1 : done successfully
  // 2 : I could not do it

  while(Wire.available()) {
    x = Wire.read();
    receiveBuffer[receivedBytes] = x;
    receivedBytes++;
   }
  Serial.print("received bytes: ");
  Serial.print(String(receiveBuffer[0]));
  Serial.print(String(receiveBuffer[1]));
  Serial.println(String(receiveBuffer[2]));

  action = receiveBuffer[0];
  direction = receiveBuffer[1];
  postDistance = receiveBuffer[2];
}

void requestEvent() {
  // DO NOT USE A DELAY IN THIS FUNCTION
  Serial.println("Slave: Requested");
  Wire.write(doneYet);
  Serial.println("Slave: Replied");
}

void setup() {
  Serial.begin(9600);
  delay(5000);
  Wire.begin(BPILL_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(LED_PIN, OUTPUT);
  clawServo.attach(SERVO_PIN);
  clawServo.write(rest);
  delay(500);
  Serial.println("Setup");
}

void loop() {
  //Note: slave will still respond to the master as actions in this loop are being carried out

  switch (action){
    Serial.println("Switch statement:");
    case PING:
    break;

    case PICKUP:
    Serial.println("Pickup switch statement");
    doneYet = (byte)pickupMode(direction,postDistance);
    Serial.print("doneYet:");
    Serial.println(doneYet);
    break;

    case PUTDOWN:
    break;
  }
    action = 0;
}

    // //Debugging Code with LED
    // digitalWrite(LED_PIN, HIGH);
    // delay(1000);
    // digitalWrite(LED_PIN,LOW);
    // delay(1000);