#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>

#define closed 37 //degrees
#define rest 60 //degrees
//RACK & PINION
#define pinionDiameter 25//mm

boolean clawPickupAttempt (Servo);
void writeSpeed(Servo , int , int );
void moveToRest(Servo );
boolean clawDropoffAttempt(Servo);
boolean pickUpStone(Servo);
float writeToRackAndPinion (float, float);
