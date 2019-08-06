#include <movement.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>
#include <sensors.h>

const float pinionDistanceMultiplier = pinionDiameter*PI/48; //change this

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
  //ourServo.write(20); 
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
 *Takes desired position (setPos - float in cm) and current position (rackPosition - float in cm)
 *Returns new position of rack as a float
 *Note: The rack overshoots by 1 - 2 cm, but the distance value returned was what was entered as a parameter (worse on short distances, better on big)
 */
float writeToRackAndPinion (float setPos, float rackPosition){
  int counter = 0;
  int currentStateCLK;
  int previousStateCLK = digitalRead(INPUT_CLK); 
  String encdir ="";
  float distance =0;
  float targetDistance = setPos - rackPosition;
  Serial.println("targetDistance");
  Serial.println(targetDistance);
  
  pwm_start(PINION_IN, 100000, 250, 0, 1);
  pwm_start(PINION_OUT, 100000, 250, 0, 1);

if (targetDistance > 0){
  while(distance < targetDistance){
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
   if (millis()%500==0){
    //  Serial.print("Direction: ");
    //  Serial.print(encdir);
    //  Serial.print(" -- Value: ");
    //  Serial.println(counter);
    //  Serial.println(distance);
   }
     //CHECK
     distance = counter*pinionDistanceMultiplier;
      // keep powering the motor until the distance is right
     if (setPos>rackPosition){
      pwm_start(PINION_OUT, 100000, 250, rackSpeed, 0);
      pwm_start(PINION_IN, 100000, 250, 0, 0);

     }
     else{
      pwm_start(PINION_IN, 100000, 250, rackSpeed, 0);
      pwm_start(PINION_OUT, 100000, 250, 0, 0);
     }
      // Update previousStateCLK with the current state
      previousStateCLK = currentStateCLK; 
   }
} 
else{
  while(distance > targetDistance){
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
  //  if (millis()%500==0){
  //    Serial.print("Direction: ");
  //    Serial.print(encdir);
  //    Serial.print(" -- Value: ");
  //    Serial.println(counter);
  //    Serial.println(distance);
  //  }
     //CHECK
     distance = counter*pinionDistanceMultiplier;
      // keep powering the motor until the distance is right
     if (setPos>rackPosition){
      pwm_start(PINION_OUT, 100000, 250, rackSpeed, 0);
      pwm_start(PINION_IN, 100000, 250, 0, 0);

     }
     else{
      pwm_start(PINION_IN, 100000, 250, rackSpeed, 0);
      pwm_start(PINION_OUT, 100000, 250, 0, 0);
     }
      // Update previousStateCLK with the current state
      previousStateCLK = currentStateCLK; 
   }
} 
      pwm_start(PINION_IN, 100000, 250, 0, 0);
      pwm_start(PINION_OUT, 100000, 250, 0, 0);

       Serial.print("Direction: ");
       Serial.print(encdir);
       Serial.print(" -- Value: ");
       Serial.println(counter);
       Serial.println(distance);

   return rackPosition + distance;
}

void resetRack (){
  pwm_start(PINION_IN, 100000, 250, 0, 1);
  pwm_start(PINION_OUT, 100000, 250, 0, 1);
  while (digitalRead(RACK_LIMIT_SWITCH)==LOW){
    pwm_start(PINION_IN, 100000, 250, rackSpeed, 0);
    pwm_start(PINION_OUT, 100000, 250, 0, 0);
  }
  pwm_start(PINION_IN, 100000, 250, 0, 0);
  pwm_start(PINION_OUT, 100000, 250, 0, 0);
}

void fullSendRack(){
  pwm_start(PINION_IN, 100000, 250, 0, 1);
  pwm_start(PINION_OUT, 100000, 250, 0, 1);
  while (digitalRead(RACK_LIMIT_SWITCH)==LOW){
    pwm_start(PINION_IN, 100000, 250, 0, 0);
    pwm_start(PINION_OUT, 100000, 250, rackSpeed, 0);
  }
  pwm_start(PINION_IN, 100000, 250, 0, 0);
  pwm_start(PINION_OUT, 100000, 250, 0, 0);
}

//LEAD SCREW CONTROL

/*
 *Raise arm platform to top of lead screw
 */
void raiseArmToTop(Servo ourServo){
  ourServo.write(closed);
  Serial.println ("raiseArmToTop");
  pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 1);
  pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 1);

  Serial.print("Switch status:");
  Serial.println(digitalRead(LEAD_SCREW_TOP_SWITCH));

  while (digitalRead(LEAD_SCREW_TOP_SWITCH)==LOW){
    pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, liftSpeed, 0);
    pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
    delay(100);
  }
       
  pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
  pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
}

/*
 *Lower arm platform to bottom of lead screw
 */
void lowerArmToBottom(){
  //Initialize motors
  pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 1);
  pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 1);

  while (digitalRead(LEAD_SCREW_BOTTOM_SWITCH)==LOW){
    //Turn motor on upwards
    pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
    pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, descendSpeed, 0);
    delay(100);
  }
  //Stop motor
  pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
  pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
}

boolean lowerArmToPost (Servo ourServo){
  
    ourServo.write(rest);
    pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 1);
    pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 1);

    // Serial.print("Right claw switch: ");
    // Serial.println(digitalRead(RIGHT_CLAW_SWITCH_PIN));
    // Serial.print("Left claw switch: ");
    // Serial.println(digitalRead(LEFT_CLAW_SWITCH_PIN));
    // Serial.print("Lead screw bottom switch: ");
    // Serial.println(digitalRead(LEAD_SCREW_BOTTOM_SWITCH));


//TO FIX = CHANGE SECOND LEFT SWITCH CONDITIONAL STATEMENT, TO RIGHT SWITCH CONDITIONAL STATEMENT - RIGHT SWITCH ALWAYS HIGH!
  while (digitalRead(LEFT_CLAW_SWITCH_PIN)== LOW && digitalRead(LEFT_CLAW_SWITCH_PIN)== LOW && digitalRead(LEAD_SCREW_BOTTOM_SWITCH) !=HIGH ){
    pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
    pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 150, 0);
    delay (100);
    //No serial print statements in this loop
  }

  if(digitalRead(LEAD_SCREW_BOTTOM_SWITCH) == HIGH){
    return false;
  }

  pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
  pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);

    // Serial.print("Right claw switch: ");
    // Serial.println(digitalRead(RIGHT_CLAW_SWITCH_PIN));
    // Serial.print("Left claw switch: ");
    // Serial.println(digitalRead(LEFT_CLAW_SWITCH_PIN));
    // Serial.print("Lead screw bottom switch: ");
    // Serial.println(digitalRead(LEAD_SCREW_BOTTOM_SWITCH));
    
    return true;
}

void movePinionOut (float targetDistance){
  int counter = 0;
  int currentStateCLK;
  int previousStateCLK = digitalRead(INPUT_CLK); 
  String encdir ="";
  float distance = 0;

  float distanceOffset = 3.525; //distance offset from arm to sonar in cm
  targetDistance += distanceOffset;
  
  pwm_start(PINION_IN, 100000, 250, 0, 1);
  pwm_start(PINION_OUT, 100000, 250, 0, 1);

   Serial.println("targetDistance");
   Serial.println(targetDistance);

  // If the sonar sends a crazy value, just make it 30cm
  if(targetDistance > 20){
    targetDistance = 20;
    Serial.print("Target distance is insane, changing it to 30cm");
  }

  while(distance < targetDistance){
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
     //CHECK
     distance = counter*pinionDistanceMultiplier;
      // keep powering the motor until the distance is right
      pwm_start(PINION_IN, 100000, 250, 0, 0);
      pwm_start(PINION_OUT, 100000, 250, rackSpeed, 0);
     
      // Update previousStateCLK with the current state
      previousStateCLK = currentStateCLK; 
   }
      pwm_start(PINION_IN, 100000, 250, 0, 0);
      pwm_start(PINION_OUT, 100000, 250, 0, 0);

      //  Serial.print("Direction: ");
      //  Serial.print(encdir);
      //  Serial.print(" -- Value: ");
      //  Serial.println(counter);
      Serial.println(distance);
}

// void raiseArm(float setHeight){
//   pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 1);
//   pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 1);
//   int counter = 0;
//   float heightMultiplier = 1; //CHANGE
//   float currentHeight = 0;

//   while (currentHeight != setHeight){
//     //add the QRD as a counter in here.
//     pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, liftSpeed, 0);
//     pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
//     delay(100);
//     currentHeight = counter*heightMultiplier;
//   }
       
//   pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
//   pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
// }


//raises the arm to the correct height in INCHES:
// Should we do the height off the ground, the height off the robot, or the height from bottom arm switch?
// void raiseArm(float setHeight){
//   pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 1);
//   pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 1);
//   int counter = 0;
//   float heightMultiplier = 1/16; 
//   float currentHeight = 0;
//   boolean prevQRDState;
//   boolean currentQRDState = OFF;

//   pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 200, 0);
//   pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);

//   while (currentHeight != setHeight && digitalRead(LEAD_SCREW_TOP_SWITCH) != HIGH && digitalRead(LEAD_SCREW_BOTTOM_SWITCH) != HIGH){
//     currentQRDState = digitalRead(QRD_PIN);
//     //add the QRD as a counter in here.

//     if(currentQRDState!=prevQRDState){
//       counter++;
//       prevQRDState = currentQRDState;
//     }
//     currentHeight = counter*heightMultiplier;
//   }  

//   pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
//   pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
// }