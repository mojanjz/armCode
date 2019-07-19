#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>

#define closed 20 //degrees
#define rest 60 //degrees

boolean clawPickupAttempt (Servo);
void writeSpeed(Servo , int , int );
void moveToRest(Servo );