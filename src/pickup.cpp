#include <pickup.h>
#include <sensors.h>
#include <movement.h>
#include <Servo.h>

int stoneTimer = 0;
boolean result = false;
boolean resultArm = false;

int pickupMode(int direction, float postDistance, Servo armServo) {

int complete = IN_PROGRESS; //Status of complete pickup operation

//float targetLength = postDistance;
int state = GOING_TO_MAX;
//int state = ROTATING_ARM_TO_SIDE;

//ensure rack is at position 0 when starting robot/ running code!
// int rackDistance = 0;

//Servo armServo;
Servo clawServo;
//armServo.attach(ARM_SERVO_PIN);
clawServo.attach(CLAW_SERVO_PIN);

// bool pickedUpYet = false;
Serial.println("Pickup Mode:");

//MAKE SURE EVERTHING IS SET UP PROPERLY TO START
resetRack(); //CHANGE
// Serial.println("Writing to straight intially");
armServo.write(straight);
delay(2000);
//lowerArmToBottom(); CHANGE

while (complete == IN_PROGRESS){

    Serial.println("Pickup while loop:");

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
            if(direction == LEFT){
              Serial.println("Rotating arm to left:");
             armServo.write(190); 
             delay(2000);
            }
            else if(direction == RIGHT){
            Serial.println("Rotating arm to right:");
            armServo.write(0);
            delay(2000);
            } else {
                Serial.println("No valid direction sent to slave.");
                complete = UNABLE;
                break;
            }
            state = EXPAND_ARM;
            //complete = COMPLETE;
            Serial.println("Going to expand");
        break;

        case EXPAND_ARM:
            Serial.println("Expand Arm:");

            //CHANGE THIS BACK
            
            movePinionOut(postDistance);
            //movePinionOut(10.00);
            state = LOWERING_ARM;
            //complete = COMPLETE;
        break;

        case LOWERING_ARM:
            Serial.println("Lowering Arm:");
            resultArm = lowerArmToPost(clawServo);
            Serial.print("lower limit switch status: ");
            Serial.println(digitalRead(LEAD_SCREW_BOTTOM_SWITCH));
            //If the lead screw bottom switch gets pressed, we were unable to pickup the stone
            if(resultArm == false){
             complete = UNABLE;
             break;
            }

            stoneTimer = millis();
            state = PICKUP_STONE;
        break;

        case PICKUP_STONE:
            while(millis() - stoneTimer < stoneDelay){
                pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, liftSpeed, 0);
                pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
            }
                pwm_start(LEAD_SCREW_UP_PIN, 100000, 250, 0, 0);
                pwm_start(LEAD_SCREW_DOWN_PIN, 100000, 250, 0, 0);
            Serial.println("Pickup Stone:");
            result = clawPickupAttempt(clawServo);

            //COMMENT IN IF YOU WANT IT TO SEND UNSUCCESSFUL WHEN STONE ISNT PICKED UP

            //if the claw switch wasnt pressed, we didnt pick up a stone. Unsuccessful.
            if(result == false){
                raiseArmToTop(armServo);
                resetRack();
                armServo.write(straight);
                lowerArmToBottom();
                complete = UNABLE; 
                break; 
            }
            state = RAISE_ARM_AFTER_PICKUP;
        break;

        //Set a timer for like 2s, so it doesnt go all the way to the top??
        case RAISE_ARM_AFTER_PICKUP:
            Serial.println("Raising arm after pickup:");
            raiseArmToTop(clawServo);
            state = CONTRACT_ARM;
            //complete = COMPLETE;
        break;

        case CONTRACT_ARM:
            Serial.println("Contracting Arm:");
            resetRack();
            state = ROTATING_ARM_TO_FRONT;
            //complete = COMPLETE;
        break;

        case ROTATING_ARM_TO_FRONT:
            Serial.println("Rotating arm to front:");
            armServo.write(straight); 
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
    }
    
    return complete;
}