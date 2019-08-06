#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>
//CLAW
#define closed 0 //degrees
#define rest 20 //degrees
//RACK & PINION
#define pinionDiameter 2.5//cm
//LEAD SCREW
#define descendSpeed 170
#define liftSpeed 220
#define rackSpeed 165
//BOTTOM SERVO
#define straight 150
#define leftAngle 220
#define rightAngle 90

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