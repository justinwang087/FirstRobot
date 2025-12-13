#include "autons.hpp"
#include "RobotConfig.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/util.hpp"
#include "pros/motors.h"
#include "outtake.hpp"


void side1(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 
    pros::delay(1000);
    chassis.setPose(48.43,-17,180);
    chassis.moveToPose(48,-44,180,1000);
    loader.set_value(true);
    chassis.moveToPose(48,-44,90,1000);
    intake.move(-127);
    chassis.moveToPose(67,-44,90,500, {.minSpeed = 50});
    convSpeed = -127;
    Out.set_value(true);

}

void side2(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 
    chassis.setPose(48.43,15,0);

    //move to loader
    chassis.moveToPose(65.2,38.65,90,15000,{.lead = 0.6,.maxSpeed=90, .minSpeed = 20});
    loader.set_value(true);
    intake.move(-127);
    convSpeed=-127;
    chassis.moveToPose(73.2, 38.65, 90, 1000,{.minSpeed = 10});
    loading = true;
    pros::delay(2000);
    loader.set_value(false);
    lifter.set_value(true);
    chassis.waitUntilDone();

     //move to long goal
    chassis.moveToPose(34.36,38.84,90,1250, {.forwards = false, .minSpeed = 50});
    chassis.waitUntilDone();
    Out.set_value(true);
    loading = false;
    intake.move(-127);
    convSpeed=-127;
    pros::delay(2250);
    intake.move(0);
    convSpeed=-0;
}

void henryhelp() {
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0, 3, 500, {.minSpeed=40});

}

void middle1() {
    chassis.setPose(48,-12,90);
    lifter.set_value(false);
    loader.set_value(false);


    intake.move(-127);
    chassis.moveToPose(24,-12, 90, 1000, {.lead = 4, .minSpeed = 20});

    
}
