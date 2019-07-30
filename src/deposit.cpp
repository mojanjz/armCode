#include <pickup.h>
#include <sensors.h>
#include <movement.h>
#include <Servo.h>
#include <deposit.h>

int depositMode(int gauntletNum){
    int complete = IN_PROGRESS; //Status of complete pickup operation
    int state = RAISING_ARM;

    Serial.println("Deposit Mode:");

    Servo armServo;
    Servo clawServo;
    armServo.attach(ARM_SERVO_PIN);
    clawServo.attach(CLAW_SERVO_PIN);
    armServo.write(rest);

    while (complete == IN_PROGRESS){

    //    
    switch (state) {

        case RAISING_ARM:
        //complete = COMPLETE;
        break;

        case TURNING_ARM:
        if(gauntletNum == 0){
            armServo.write(34);
        }
        else if(gauntletNum==1){
            armServo.write(56);
        }
         else if(gauntletNum==2){
            armServo.write(75);
        }
         else if(gauntletNum==3){
            armServo.write(98);
        }
         else if(gauntletNum==4){
            armServo.write(119);
        }
         else if(gauntletNum==5){
            armServo.write(141);
        }
        else{
            complete = UNABLE;
            break;
        }

        state = EXTEND_ARM;
        break;

        case EXTEND_ARM:
           if(gauntletNum == 0 ||gauntletNum == 5 ){
            movePinionOut(17);
        }
        else if(gauntletNum==1 || gauntletNum==4){
            movePinionOut(19);
        }
         else if(gauntletNum==2 || gauntletNum==3){
            movePinionOut(25);
        }
       
        else{
            complete = UNABLE;
            break;
        }

        state = DROP_STONE;
        break;

        case DROP_STONE:
        clawServo.write(rest);
        resetRack();
        complete = COMPLETE;
        break; 
    }
    break;

    }
    return complete;
}
