#ifndef PICKUP_H
#define PICKUP_H

#include <Arduino.h>
#include <Servo.h>
#include <movement.h>

#define GOING_TO_MAX 0
#define ROTATING_ARM_TO_SIDE 1
#define EXPAND_ARM 2
#define LOWERING_ARM 3
#define PICKUP_STONE 4
#define RAISE_ARM_AFTER_PICKUP 5
#define CONTRACT_ARM 6
#define ROTATING_ARM_TO_FRONT 7
#define LOWERING_ARM_TO_DRIVE 8
#define ADJUST_CLAW_POSITIONING 9

#define stoneDelay 100

#define DISTANCE_MULTIPLIER 1 //mapping sonar distance to encoder distance

int pickupMode(int direction, float postDistance, Servo);

// bool atThePost;

//extern Servo clawServo;

//extern Servo armServo;

#endif
