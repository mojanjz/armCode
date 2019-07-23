#include "movement.h"
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>
#include <sensors.h>

const int pinionDistanceMultiplier = pinionDiameter*PI/24;

boolean alignClaw (Servo ourServo){
  bool successful = false;


  return successful;
}

//CLAW CONTROL
/*
*Attempts to pickup an infinity stone one time.
*Returns true or false based on whether the stone was picked up
*Parameters: Servo, the servo performing the action.
 */
boolean clawPickupAttempt(Servo ourServo)
{
  boolean successful = false;
  Serial.println("Attempting to close servo on inf stone:");
  ourServo.write(closed);
  //wait for servo to get there
  delay(1000);
  Serial.print("Status:");
  Serial.println(successful);
  //check if switch is actuated
  successful = digitalRead(PICKUP_SWITCH_PIN);

  return successful;
}

//RACK & PINION CONTROL
/*
 *Moves rack and pinion to specified position
 *Takes desired position (setPos - float ) and current position (rackPosition - float)
 *Returns new position of rack as a float
 */
float writeToRackAndPinion (float setPos, float rackPosition){
  int counter = 0;
  int currentStateCLK;
  int previousStateCLK = digitalRead(INPUT_CLK);; 
  String encdir ="";

  while(rackPosition != setPos){
    counter = 0;

    // Read the current state of inputCLK
   currentStateCLK = digitalRead(INPUT_CLK);
   // If the previous and the current state of the inputCLK are different then a pulse has occured
   if (currentStateCLK != previousStateCLK){ 
     // If the inputDT state is different than the inputCLK state then the encoder is rotating counterclockwise
     if (digitalRead(INPUT_DT) != currentStateCLK) { 
       counter --;
       encdir ="CCW";
     } else {
       // Encoder is rotating clockwise
       counter ++;
       encdir ="CW";
     }
   }
     Serial.print("Direction: ");
     Serial.print(encdir);
     Serial.print(" -- Value: ");
     Serial.println(counter);
     //CHECK
     rackPosition = rackPosition + counter*pinionDistanceMultiplier;
      // keep powering the motor until the distance is right
     if (setPos>rackPosition){
      pwm_start(PINION_OUT, 100000, 250, 150, 1);
      pwm_start(PINION_IN, 100000, 250, 0, 1);

     }
     else{
      pwm_start(PINION_IN, 100000, 250, 150, 1);
      pwm_start(PINION_OUT, 100000, 250, 0, 1);
     }
      // Update previousStateCLK with the current state
      previousStateCLK = currentStateCLK; 
   } 
   return rackPosition;
}

//  int counter = 0; 
//  int currentStateCLK;
//  int previousStateCLK; 


//  String encdir ="";
//  float distance;

//  void setup() { 
   
//    // Set encoder pins as inputs  
//    pinMode (inputCLK,INPUT);
//    pinMode (inputDT,INPUT);
   
//    // Setup Serial Monitor
//    Serial.begin (9600);
   
//    // Read the initial state of inputCLK
//    // Assign to previousStateCLK variable
//    previousStateCLK = digitalRead(inputCLK);

//  } 

//  void loop() { 
  
//   // Read the current state of inputCLK
//    currentStateCLK = digitalRead(inputCLK);
    
//    // If the previous and the current state of the inputCLK are different then a pulse has occured
//    if (currentStateCLK != previousStateCLK){ 
       
//      // If the inputDT state is different than the inputCLK state then 
//      // the encoder is rotating counterclockwise
//      if (digitalRead(inputDT) != currentStateCLK) { 
//        counter --;
//        encdir ="CCW";
       
//      } else {
//        // Encoder is rotating clockwise
//        counter ++;
//        encdir ="CW";
       
//      }
//      Serial.print("Direction: ");
//      Serial.print(encdir);
//      Serial.print(" -- Value: ");
//      Serial.println(counter);

//      distance = counter*DISTANCEMULTIPLIER;

//      if (distance != 5){
//        // keep powering the motor until the distance is right
//       pwm_start(IN, 100000, 250, 150, 1);
//       pwm_start(OUT, 100000, 250, 0, 1);
//      }
//      else{
//        //stop the motor it has reached its destination
//        pwm_start(IN, 100000, 250, 0, 1);
//        pwm_start(OUT, 100000, 250, 0, 1);
//      }

//    } 
//    // Update previousStateCLK with the current state
//    previousStateCLK = currentStateCLK; 
//  }