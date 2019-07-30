#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>
//CLAW
#define closed 0 //degrees
#define rest 15 //degrees
//RACK & PINION
#define pinionDiameter 2.5//cm
//LEAD SCREW
#define descendSpeed 170
#define liftSpeed 220
#define rackSpeed 100
//BOTTOM SERVO
#define straight 25
#define leftAngle 90
#define rightAngle 0

boolean clawPickupAttempt (Servo);
void writeSpeed(Servo , int , int );
void moveToRest(Servo );
boolean clawDropoffAttempt(Servo);
boolean pickUpStone(Servo);
float writeToRackAndPinion (float, float);
void raiseArmToTop(Servo);
void lowerArmToBottom();
void lowerArmToPost(Servo);
void resetRack ();
void fullSendRack();
void movePinionOut (float);
void raiseArm(float);