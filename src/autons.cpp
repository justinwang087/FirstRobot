#include "autons.hpp"
#include "RobotConfig.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/util.hpp"
#include "pros/motors.h"
#include "outtake.hpp"


void side1(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 
    Out.set_value(true);
    chassis.setPose(48.43,-17,180);
    chassis.moveToPose(48,-46.5,180,2000);
    loader.set_value(true);
    chassis.turnToPoint(67, -46, 1500);
    intake.move(-127);
    convSpeed = -127;
    chassis.moveToPose(65,-46,90,3000, {.minSpeed = 50});
    chassis.waitUntilDone();
    pros::delay(750);

    chassis.moveToPose(27,-46,90,1000, {.forwards = false, .minSpeed = 30});
    chassis.waitUntilDone();
    Out.set_value(false);
    

}

void side2(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 
    Out.set_value(true);
    chassis.setPose(48.43,17,0);
    chassis.moveToPose(48,45,0,2000);
    loader.set_value(true);
    chassis.turnToPoint(67, 46, 1500);
    intake.move(-127);
    convSpeed = -127;
    chassis.moveToPoint(60.5,46,3000);
    chassis.waitUntilDone();
    pros::delay(750);

chassis.moveToPose(27.5,48,90,1000, {.forwards = false, .minSpeed = 30});
    chassis.waitUntilDone();
    Out.set_value(false);
    
}

void skills() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 
    Out.set_value(true);
    chassis.setPose(48.43,17,0);
    chassis.moveToPose(48,45,0,2000);
    loader.set_value(true);
    chassis.turnToPoint(67, 46, 1500);
    intake.move(-127);
    convSpeed = -127;
    chassis.moveToPoint(60.5,46,3000);
    chassis.waitUntilDone();
    pros::delay(2250);

chassis.moveToPose(27.5,48,90,1000, {.forwards = false, .minSpeed = 30});
    chassis.waitUntilDone();
    Out.set_value(false);
    pros::delay(3500);
    chassis.moveToPoint(48, 48, 1250);
    loader.set_value(false);
    convSpeed=0;
    intake.move(0);
    chassis.turnToPoint(60.5, 0, 1500);
    chassis.moveToPose(60.5, 0, 180, 2500, {.minSpeed=127});
    chassis.moveToPoint(60.5, -18, 2500, {.minSpeed=127});
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
