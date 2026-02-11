#include "autons.hpp"
#include "RobotConfig.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/util.hpp"
#include "pros/motors.h"
#include "outtake.hpp"
#include "pros/rtos.hpp"

void side2(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 
    chassis.setPose(-52,18,0);
    loader.set_value(true);
    pros::delay(400);
    chassis.moveToPose(-48,49,0,2000);
    chassis.turnToPoint(-72,48,1100);
    convSpeed = 127;
    chassis.moveToPose(-72,48,270,1100,{.minSpeed = 90});
    pros::delay(1500);
    chassis.moveToPose(-25,48,270,2000,{.forwards = false, .lead=0.2, .maxSpeed=55});
    pros::delay(1500);
    outake.move(-127);
    pros::delay(3000);
    chassis.moveToPoint(-48, 48, 1000, {.minSpeed=20});
    descore.set_value(true);
    chassis.turnToHeading(240, 750, {.minSpeed=20, .earlyExitRange=5});
    chassis.moveToPose(-25, 58.7, 270, 2000, {.forwards=false, .lead=0.20});
    
    chassis.moveToPose(-7,58.7,270,2000,{.forwards=false,.lead = 0.3, .minSpeed=50});
    descore.set_value(false);

    
}
void side1(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 

    chassis.setPose(52,18,0);
    loader.set_value(true);
    pros::delay(400);
    chassis.moveToPose(48,48,0,2000);
    chassis.turnToPoint(72,48,1100);
    convSpeed = 127;
    chassis.moveToPose(72,48,90,1100,{.minSpeed = 80});
    pros::delay(1300);
    chassis.moveToPose(25,48,90,2000,{.forwards = false, .lead=0.3, .maxSpeed=65});
    pros::delay(1500);
    outake.move(-127);
    pros::delay(3000);
    chassis.moveToPoint(48, 48, 1000, {.minSpeed=20, .earlyExitRange=4});
    descore.set_value(true);
    chassis.turnToHeading(80, 750, {.minSpeed=20, .earlyExitRange=5});
    chassis.moveToPose(24, 38.5, 90, 2000, {.forwards=false, .lead=0.25});
    // chassis.turnToHeading(90, 1000);
    chassis.moveToPose(6, 38.5, 90, 2000, {.forwards=false, .lead=0.3, .minSpeed=47.5});
    descore.set_value(false);
}


void skills() {
   chassis.setPose(47,-14,-90);
   chassis.turnToHeading(-103,1000);
   chassis.moveToPose(19,-24,-103,1000, {.minSpeed = 65});
   intake.move(127);
   convSpeed = 120;
   pros::delay(900);
   loader.set_value(true);
   chassis.turnToHeading(-226,1000);
   pros::delay(1000);
   chassis.moveToPose(10.5,-10,-218,1000, {.forwards=false, .minSpeed =60});
   pros::delay(750);
   outake.move(127);
   //chassis.moveToPose(-48,49,-226,2000);
}

void middle1() {
    chassis.setPose(48,-12,90);
    loader.set_value(false);


    intake.move(-127);
    chassis.moveToPose(24,-12, 90, 1000, {.lead = 4, .minSpeed = 40});

    
}
