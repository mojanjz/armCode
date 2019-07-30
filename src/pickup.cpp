#include <pickup.h>
#include <sensors.h>
#include <movement.h>
#include <Servo.h>

int stoneTimer=0;

int pickupMode(int direction, int postDistance) {
    
int complete = IN_PROGRESS; //Status of complete pickup operation
float targetLength = postDistance + ARM_SONAR_OFFSET;
int result = 0; //Results of individual commands
int state = GOING_TO_MAX;
//int state = ROTATING_ARM_TO_SIDE;

//ensure rack is at position 0 when starting robot/ running code!
int rackDistance = 0;

Servo armServo;
Servo clawServo;
armServo.attach(ARM_SERVO_PIN);
clawServo.attach(CLAW_SERVO_PIN);


bool pickedUpYet = false;
Serial.println("Pickup Mode:");

armServo.write(82);

while (complete == IN_PROGRESS){

    Serial.println("Pickup while loop:");

    //CHECKS:
    // are we at the highest height?
    switch (state) {

        case GOING_TO_MAX:
        Serial.println("Raising arm to max:");
        raiseArmToTop(clawServo);
        state = ROTATING_ARM_TO_SIDE;
        //complete = COMPLETE;
        break;

        case ROTATING_ARM_TO_SIDE:
        // call servo and write to 90 depending on which side the post is on.
        Serial.println("Rotating arm to side!");
        // if(direction == LEFT){
            Serial.println("Rotating arm to left:");
            armServo.write(95); //CHANGE back to 2!!!
        // }
        // else if(direction == RIGHT){
        //     Serial.println("Rotating arm to right:");
        //     armServo.write(171); //5deg sets the arm motor almost exactly 90deg to the right of initial starting point
        // } else {
        //     Serial.println("No valid direction sent to slave.");
        // }
        state = EXPAND_ARM;
        //complete = COMPLETE;
        break;

        case EXPAND_ARM:
        Serial.println("Expand Arm:");
        //rackDistance = writeToRackAndPinion(targetLength, rackDistance);
        //rackDistance = writeToRackAndPinion(5, 0);
        movePinionOut(5.00);
        //state = LOWERING_ARM;
        state = LOWERING_ARM;
        //complete = COMPLETE;
        break;

        case LOWERING_ARM:
            Serial.println("Lowering Arm:");
            lowerArmToPost(clawServo);
            stoneTimer = millis();
            state = PICKUP_STONE;
            //Serial.println("Completed lowering Arm");
            // complete = COMPLETE;
        break;

    //     // //MAKE SURE WE ADD COUNTER FOR PICKUP ATTEMPTS!!!!!
        case PICKUP_STONE:
        while(millis() - stoneTimer < stoneDelay){
            pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, liftSpeed, 0);
            pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
        }
            pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
            pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
        Serial.println("Pickup Stone:");
        result = clawPickupAttempt(clawServo);
        // if (result == 0){
        //     //If stone wasn't successfully collected, readjust claw positioning
        //     // state = ADJUST_CLAW_POSITIONING;
        //             complete = COMPLETE;
        // }
        //else{
        state = RAISE_ARM_AFTER_PICKUP;

                     //complete = COMPLETE;
        //}
        //complete = COMPLETE;
        break;

        case RAISE_ARM_AFTER_PICKUP:
        Serial.println("Raising arm after pickup:");
        raiseArmToTop(clawServo);
        state = CONTRACT_ARM;
        //complete = COMPLETE;
        break;

    
        case CONTRACT_ARM:
        Serial.println("Contracting Arm:");
        //Call rack and pinion back to retracted position
        //Drop claw to lowest height possible
        //rackDistance = writeToRackAndPinion(0, rackDistance);
        resetRack();
        state = ROTATING_ARM_TO_FRONT;
        //complete = COMPLETE;
        break;

        case ROTATING_ARM_TO_FRONT:
        Serial.println("Rotating arm to front:");
        armServo.write(82); //95 is 90 degrees with the front of the chassis
        state = LOWERING_ARM_TO_DRIVE;
        //complete = COMPLETE;
        break;

        case LOWERING_ARM_TO_DRIVE:
        Serial.println("Lowering Arm to drive:");
        lowerArmToBottom();
        complete = COMPLETE;
        break;

    //     // case ADJUST_CLAW_POSITIONING:
    //     // Serial.println("Could not pick up stone. :( Try another post");
    //     // //call function to adjust
    //     // // if successful, state = RAISE_ARM_AFTER_PICKUP
    //     // // if not successful, return 0 to the master.
    //     // return UNABLE;
    //     // //break

    // }
    }


    // change the angle to 90 degrees in the given direction
    // IS ARM LENGTH AT THE RIGHT DISTANCE?
    // ARE YOU AT THE RIGHT HEIGHT
    // DID YOU PICK UP A STONE?

}
return complete;
}