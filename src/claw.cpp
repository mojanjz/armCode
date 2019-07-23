#include "claw.h"
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Servo.h>
#include <sensors.h>

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
  successful = digitalRead(PICKUP_SWITCH);

  return successful;
}
// boolean clawPickupAttempt(Servo ourServo)
// {
//   boolean successful = false;
//   ourServo.write(closed);
//   //wait for servo to get there
//   delay(2000);

//   //check if switch is actuated
//   successful = digitalRead(PICKUP_SWITCH);

//   return successful;
// }

/*
*Moves servo to a specified position, int setpos, in degrees (between 0 & 180)
*at a specified speed, int speed, (between 0-800, with zero being the max speed)
 */
void writeSpeed(Servo ourServo, int speed, int setpos)
{
//int pos = 0;    // variable to store the servo position
int pause = speed/10;
int currpos = ourServo.read();
//If the current position is less than the set position, move ccw to setpos
if(currpos<setpos){
for (int pos = currpos; pos <= setpos; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    ourServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(pause);                       // waits a specified delay in ms for the servo to reach the position
  }
}
//If the current position is more than the set position, move cw to setpos
if(currpos>setpos){
for (int pos = currpos; pos >= setpos; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    ourServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(pause);                       // waits a specified delay in ms for the servo to reach the position
}
}
//If the current position is the set position, do nothing.
else{

}
}

void moveToRest(Servo ourServo)
{
  Serial.println("moving to rest");
  ourServo.write(rest);
}

boolean clawDropoffAttempt(Servo ourServo)
{
 boolean complete = true;
  writeSpeed(ourServo, 400, rest);
  // //wait for servo to get there
  return complete;
}

boolean pickUpStone(Servo ourServo){
  bool successful = false;
  for (int numAttempts = 0; numAttempts<3; numAttempts++){
    Serial.print("Attempt ");
    Serial.println(numAttempts);

    successful = clawPickupAttempt(ourServo);
    if (successful == true){
      return successful;
    }
    ourServo.write(rest);
    delay(1000);
  }
  return successful;
}