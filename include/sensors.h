#ifndef SENSORS_H
#define SENSORS_H

#define BPILL_ADDRESS 69
#define BUFFER_SIZE 3

//Pins for arm
#define LED_PIN PB14
#define PICKUP_SWITCH_PIN PA5
#define SERVO_PIN PB1
#define LEFT_CLAW_SWITCH_PIN PA4
#define RIGHT_CLAW_SWITCH_PIN PA3

//Pins for rack and pinion
#define INPUT_CLK PA1 
#define INPUT_DT PA2
#define PINION_IN PA_6
#define PINION_OUT PA_7

#define PING 0
#define PICKUP 1
#define PUTDOWN 2

#define LEFT 0
#define RIGHT 1

#define IN_PROGRESS 0
#define COMPLETE 1
#define UNABLE 2

#define MAXHEIGHT 340 // CHANGE

// global variables
extern float armHeight;
extern float armLength;
extern bool clawSuccess;
extern float armAngle;
extern byte doneYet;
#endif