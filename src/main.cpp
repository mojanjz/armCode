#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "PinNames.h"
#include <pickup.h>
#include <sensors.h>
#include <Servo.h>
#include <movement.h>

#define SONAR_ECHO PA7
#define SONAR_TRIG PA6
#define LED_PIN PB14

#define BPILL_ADDRESS 69
#define BUFFER_SIZE 3


float armHeight = 0.0;
float armLength = 0.0;
bool clawSuccess = 0.0;
float armAngle = 0.0;

int state = GOING_TO_MAX;
int action = 0;//CHANGE
int direction;
int postDistance;

//int counter = 0;

Servo clawServo;
//Servo armServo;

volatile byte x = 1;
byte doneYet = 1;

void receiveEvent(int);
void requestEvent(int);

/*
 *Slave recieves an event from the master
 */
void receiveEvent(int numBytes) {
  //change so that action is in progress
  doneYet = 0;

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

/*
 *Slave requests an event from master
 */
void requestEvent() {
  // DO NOT USE A DELAY IN THIS FUNCTION
  Serial.println("Slave: Requested");
  Wire.write(doneYet);
  Serial.println("Slave: Replied");
}

/*
 *Setup Loop
 */
void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("Hello");
  Wire.begin(BPILL_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(LED_PIN, OUTPUT);
  //CLAW SERVO
  // clawServo.attach(SERVO_PIN);
  // clawServo.write(rest);
  //RACK & PINION
  pinMode (INPUT_CLK,INPUT); //potentially pull up?
  pinMode (INPUT_DT,INPUT); //potentially pull up?
  pinMode(RIGHT_CLAW_SWITCH_PIN, INPUT_PULLUP);
  pinMode(LEFT_CLAW_SWITCH_PIN, INPUT_PULLUP);
  pinMode(PICKUP_SWITCH_PIN, INPUT_PULLUP);
  pinMode(RACK_LIMIT_SWITCH,INPUT_PULLUP);
  
  //Arm Servo
  //armServo.attach(ARM_SERVO_PIN);
  //Initialize the motors 
  pinMode(LEAD_SCREW_BOTTOM_SWITCH,INPUT_PULLUP);
  pinMode(LEAD_SCREW_TOP_SWITCH,INPUT_PULLUP);
  pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 1);
  pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 1);
  //If this works add other motors too

//lowerArmToBottom();
//raiseArmToTop();
//writeToRackAndPinion(10,0);
  clawServo.write(rest);
  resetRack();
//fullSendRack();
  delay(500);
  Serial.println("Setup");
}

void loop() {
  //Note: slave will still respond to the master as actions in this loop are being carried out

  switch (action){
    case PING:

    break;

    case PICKUP:
    Serial.println("Pickup switch statement");
    //change that the action is either complete, or unable
    doneYet = (byte)pickupMode(direction,postDistance);
    Serial.print("doneYet:");
    Serial.println(doneYet);
    break;

    case PUTDOWN:
    break;
  }
    action = 0;
}
