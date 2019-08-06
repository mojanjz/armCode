#ifndef SENSORS_H
#define SENSORS_H

// #define serialTesting 0 

#define BPILL_ADDRESS 69
#define BUFFER_SIZE 3

//Pins for arm
#define PICKUP_SWITCH_PIN PB13
#define CLAW_SERVO_PIN PA0
#define LEFT_CLAW_SWITCH_PIN PB12
#define RIGHT_CLAW_SWITCH_PIN PB14

//Pins for rack and pinion
#define INPUT_CLK PA5
#define INPUT_DT PA4
#define RACK_LIMIT_SWITCH PB15
#define PINION_IN PB_0
#define PINION_OUT PB_1


//Pins for lead screw
 #define LEAD_SCREW_UP_PIN PB_7
 #define LEAD_SCREW_DOWN_PIN PB_6


//CHANGE BACK
// #define LEAD_SCREW_BOTTOM_SWITCH PB10
// #define LEAD_SCREW_TOP_SWITCH PB11

#define LEAD_SCREW_BOTTOM_SWITCH PC13
#define LEAD_SCREW_TOP_SWITCH PC14

#define ARM_SERVO_PIN PA1 

#define RX3 PB11
#define TX3 PB10


//#define ARM_SONAR_OFFSET 6.065 //TO BE CHECKED

#define PING 0
#define PICKUP 1
#define PUTDOWN 2

#define LEFT 0
#define RIGHT 1

#define IN_PROGRESS 3
#define COMPLETE 1
#define UNABLE 2
#define NOT_STARTED 4

#define MAXHEIGHT 340 // CHANGE

// global variables
extern float armHeight;
extern float armLength;
extern bool clawSuccess;
extern float armAngle;
extern byte doneYet;
#endif