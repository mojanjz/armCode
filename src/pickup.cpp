#include <pickup.h>
#include <sensors.h>
#include <movement.h>
#include <Servo.h>

int pickupMode(int direction, int postDistance) {
    
int complete = IN_PROGRESS; //Status of complete pickup operation
int targetLength = postDistance - ARM_SONAR_OFFSET;
int result = 0; //Results of individual commands
int state = GOING_TO_MAX;
//ensure rack is at position 0 when starting robot/ running code!
int rackDistance = 0;

Servo armServo;
armServo.attach(ARM_SERVO_PIN);

bool pickedUpYet = false;
Serial.println("Pickup Mode:");

while ( complete == IN_PROGRESS){
    Serial.println("Pickup while loop:");

    //CHECKS:
    // are we at the highest height?
    switch (state) {
        case GOING_TO_MAX:
        Serial.println("Raising arm to max:");
        raiseArmToTop();
        state = ROTATING_ARM_TO_SIDE;
        //complete = COMPLETE;

        break;

        // case ROTATING_ARM_TO_SIDE:
        // // call servo and write to 90 depending on which side the post is on.
        // if(direction == LEFT){
        //     Serial.println("Rotating arm to left:");
        //     armServo.write(90); //CHANGE THIS TO BE CORRECT ANGLE
        // }
        // else{
        //     Serial.println("Rotating arm to right:");
        //     armServo.write(180); //CHANGE THIS TO BE CORRECT ANGLE
        // }
        // //state = EXPAND_ARM;
        // complete = COMPLETE;
        // break;

        // case EXPAND_ARM:
        // Serial.println("Expand Arm:");
        // rackDistance = writeToRackAndPinion(targetLength, rackDistance);
        // state = LOWERING_ARM;
        // break;

        // case LOWERING_ARM:
        // Serial.println("Lowering Arm:");
        // lowerArmToPost();
        // state = PICKUP_STONE;
        // break;

        // //MAKE SURE WE ADD COUNTER FOR PICKUP ATTEMPTS!!!!!

        // case PICKUP_STONE:
        // Serial.println("Pickup Stone:");
        // result = clawPickupAttempt(clawServo);
        // if (result == 0){
        //     //If stone wasn't successfully collected, readjust claw positioning
        //     state = ADJUST_CLAW_POSITIONING;
        // }
        // else{
        //      state = RAISE_ARM_AFTER_PICKUP;
        // }
        // //complete = COMPLETE;
        // break;

        // case RAISE_ARM_AFTER_PICKUP:
        // Serial.println("Raising arm after pickup:");
        // raiseArmToTop();
        // state = CONTRACT_ARM;
        // break;

    
        // case CONTRACT_ARM:
        // Serial.println("Contracting Arm:");
        // //Call rack and pinion back to retracted position
        // //Drop claw to lowest height possible
        // rackDistance = writeToRackAndPinion(0, rackDistance);
        // state = ROTATING_ARM_TO_FRONT;
        // break;

        // case ROTATING_ARM_TO_FRONT:
        // Serial.println("Rotating arm to front:");
        // armServo.write(0); //CHANGE TO BE CORRECT ANGLE
        // state = LOWERING_ARM_TO_DRIVE;
        // break;

        // case LOWERING_ARM_TO_DRIVE:
        // Serial.println("Lowering Arm to drive:");
        // lowerArmToBottom();
        // complete = COMPLETE;
        // break;

        // case ADJUST_CLAW_POSITIONING:
        // Serial.println("Could not pick up stone. :( Try another post");
        // //call function to adjust
        // // if successful, state = RAISE_ARM_AFTER_PICKUP
        // // if not successful, return 0 to the master.
        // return UNABLE;
        // //break

    }
    }


    // change the angle to 90 degrees in the given direction
    // IS ARM LENGTH AT THE RIGHT DISTANCE?
    // ARE YOU AT THE RIGHT HEIGHT
    // DID YOU PICK UP A STONE?

return complete;
}