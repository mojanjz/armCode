#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>
//CLAW
#define closed 15 //degrees
#define rest 30 //degrees
//RACK & PINION
#define pinionDiameter 2.5//cm
//LEAD SCREW
#define descendSpeed 170
#define liftSpeed 220
#define rackSpeed 165
//BOTTOM SERVO
#define straight 90
#define leftAngle 180
#define rightAngle 0

boolean clawPickupAttempt (Servo);
void writeSpeed(Servo , int , int );
void moveToRest(Servo );
boolean clawDropoffAttempt(Servo);
boolean pickUpStone(Servo);
float writeToRackAndPinion (float, float);
void raiseArmToTop(Servo);
void lowerArmToBottom();
boolean lowerArmToPost(Servo);
void resetRack ();
void fullSendRack();
void movePinionOut (float);
void raiseArm(float);
void writeSpeed(Servo ourServo, int speed, int setpos);