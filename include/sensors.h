#ifndef SENSORS_H
#define SENSORS_H

#define BPILL_ADDRESS 69
#define BUFFER_SIZE 3

#define LED_PIN PB14
#define PICKUP_SWITCH PA5
#define SERVO_PIN PB1

#define PING 0
#define PICKUP 1
#define PUTDOWN 2

#define MAXHEIGHT 340 // CHANGE

// global variables
extern float armHeight;
extern float armLength;
extern bool clawSuccess;
extern float armAngle;
extern int doneYet;

#endif