#ifndef SENSORS_H
#define SENSORS_H

#define BPILL_ADDRESS 5
#define BUFFER_SIZE 2

#define LED_PIN PB14

#define PING 0
#define PICKUP 1
#define PUTDOWN 2

#define MAXHEIGHT 340 // CHANGE

// global variables
extern float armHeight;
extern float armLength;
extern bool clawSuccess;
extern float armAngle;

#endif