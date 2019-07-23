#include <pickup.h>
#include <sensors.h>
#include <movement.h>
#include <Servo.h>

int pickupMode(int direction, int postDistance) {
    
int complete = IN_PROGRESS; //Status of complete pickup operation
int targetLength = postDistance * DISTANCE_MULTIPLIER;
int result = 0; //Results of individual commands
int state = PICKUP_STONE;
bool pickedUpYet = false;
Serial.println("Pickup Mode:");

while ( complete == IN_PROGRESS){
    Serial.println("Pickup while loop:");

    //CHECKS:
    // are we at the highest height?
    switch (state) {

        case GOING_TO_MAX:

            break;
        case EXPAND_ARM:

            break;
        case LOWERING_ARM:
        //lower arm until claw hits post - adjust so both switches are on the post

            break;

        case PICKUP_STONE:
        Serial.println("Pickup Stone:");
        result = clawPickupAttempt(clawServo);
        if (result == 0){
            //If stone wasn't successfully collected, readjust claw positioning
            result = ADJUST_CLAW_POSITIONING;
        }
        else{
            //Contract the arm so that the robot can continue driving
            result = CONTRACT_ARM;
        }
        //complete = COMPLETE;
        break;

        case CONTRACT_ARM:
        //Call rack and pinion back to retracted position
        //Drop claw to lowest height possible
        break;

        case ADJUST_CLAW_POSITIONING:

        break;
    }
    }


    // change the angle to 90 degrees in the given direction
    // IS ARM LENGTH AT THE RIGHT DISTANCE?
    // ARE YOU AT THE RIGHT HEIGHT
    // DID YOU PICK UP A STONE?

return complete;
}