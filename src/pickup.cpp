#include <pickup.h>
#include <sensors.h>
#include <claw.h>
#include <Servo.h>

//bool atThePost = false;



int pickupMode(int direction, int postDistance) {
    int complete = IN_PROGRESS; //Status of pickup Operation
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

            break;

        case PICKUP_STONE:
        Serial.println("Pickup Stone:");
        result = clawPickupAttempt(clawServo);
        complete = COMPLETE;
        break;

        case CONTRACT_ARM:

        break;
    }
    }


    // change the angle to 90 degrees in the given direction
    // IS ARM LENGTH AT THE RIGHT DISTANCE?
    // ARE YOU AT THE RIGHT HEIGHT
    // DID YOU PICK UP A STONE?
    return complete;
}

// int pickupMode(int direction, int postDistance) {

//     int targetLength = postDistance * DISTANCE_MULTIPLIER;
//     int result = 0;
//     bool pickedUpYet = false;

//     while (doneYet == false){
//     //CHECKS:
//     // are we at the highest height?
//     switch (state) {
//         case GOING_TO_MAX:
//             // if(armHeight < MAXHEIGHT) {
//             //     // raise the arm
//             // }
//             // else {
//             //     state = EXPAND_ARM;
//             // }
//             // doneYet = 0; // not done yet
//             break;
//         case EXPAND_ARM:
//             // if (armLength < targetLength) {
//             //     // expand arm
//             // }
//             // else {
//             //     state = LOWERING_ARM;
//             // }
//             // doneYet = 0; //not done yet
//             break;
//         case LOWERING_ARM:
//             // if the switch is on move to pick up stone mode
//             // else keep lowering arm
//             break;
//         case PICKUP_STONE:
//            pickedUpYet = clawPickupAttempt(clawServo); // try to pick up stone
//             if (pickedUpYet == true) {
//                 result = 1; //we picked up the stone successfully
//                 //state = CONTRACT_ARM;
//                 doneYet = 1;
//             }
//             else {
//                 result = 2; //we tried 3 times, and we cant pick up the stone.
//                 // how do we assign state?
//                 doneYet = 2;
//             }
//             break;
//         case CONTRACT_ARM:
//             // if(result == 1){
//             //     doneYet = 1;
//             // }
//             // else {
//             //     doneYet = 2;
//             // }
//             break;
//     }
//     }


//     // change the angle to 90 degrees in the given direction
//     // IS ARM LENGTH AT THE RIGHT DISTANCE?
//     // ARE YOU AT THE RIGHT HEIGHT
//     // DID YOU PICK UP A STONE?
//     return doneYet;
// }