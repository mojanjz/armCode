#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>

#define closed 37 //degrees
#define rest 60 //degrees
//RACK & PINION
#define pinionDiameter 2.5//cm
//LEAD SCREW
#define descendSpeed 150
#define liftSpeed 200

boolean clawPickupAttempt (Servo);
void writeSpeed(Servo , int , int );
void moveToRest(Servo );
boolean clawDropoffAttempt(Servo);
boolean pickUpStone(Servo);
float writeToRackAndPinion (float, float);
void raiseArmToTop();
void lowerArmToBottom();
void lowerArmToPost();
