#ifndef PICKUP_H
#define PICKUP_H

#define GOING_TO_MAX 0
#define LOWERING_ARM 1
#define EXPAND_ARM 2
#define PICKUP_STONE 3
#define CONTRACT_ARM 4

#define DISTANCE_MULTIPLIER 1 //mapping sonar distance to encoder distance

int64_t pickupMode(int direction, int postDistance);
extern int state;
// bool atThePost; 

Servo clawServo;

#endif