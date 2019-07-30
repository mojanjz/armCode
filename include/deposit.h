#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <Arduino.h>
#include <Servo.h>
#include <movement.h>

#define RAISING_ARM 0
#define TURNING_ARM 1
#define EXTEND_ARM 2
#define DROP_STONE 3

int depositMode(int);

#endif