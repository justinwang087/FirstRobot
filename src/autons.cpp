#include "autons.hpp"
#include "RobotConfig.hpp"
#include "lemlib/asset.hpp"
#include "lemlib/util.hpp"
#include "pros/motors.h"

ASSET(MTTB_txt);
void BlueAwp(){
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //start pos 
    chassis.setPose(48.43,-15,180);

    //move to loader
    chassis.moveToPose(67.2,-36.18,90,15000,{.lead = 0.55, .minSpeed = 40});
    intake.move(-127);
    chassis.moveToPose(70.2, -36.18, 90, 1000,{.minSpeed = 60});
    pros::delay(5000);
    loader.set_value(false);
    lOut.set_value(true);
    rOut.set_value(true);
    lifter.set_value(true);
    chassis.waitUntilDone();

     //move to long goal
    chassis.moveToPose(32.06,-37.34,90,1000, {.forwards = false, .minSpeed = 50});
    intake.move(-127);
    outake.move(-127);
    pros::delay(2000);

}

void BlueAccomdationB(){
    //start pos
    chassis.setPose(48,0,0);
    lifter.set_value(false);
    lOut.set_value(true);
    rOut.set_value(true);

    //move to goal
    chassis.moveToPoint(36, -60, 1250, {.minSpeed = 55, .earlyExitRange=2});

    //move to the blocks under the long goal
    chassis.moveToPose(18, -48, -90, 1000, {.maxSpeed = 80, .minSpeed=10, .earlyExitRange=1});
    intake.move(127);

    chassis.moveToPose(6, -48, -90, 750, {.maxSpeed=55});

    //move back to avoid auton line
    chassis.moveToPoint(12, -48, 500, {.forwards=false, .minSpeed=30});

    //turn to the three balls
    chassis.turnToHeading(0, 750, {.minSpeed=40, .earlyExitRange=5});

    //move to three balls
    chassis.moveToPose(24, -24, 45, 1500, {.lead=0.7, .maxSpeed=80});

    //turn to goal
    chassis.turnToHeading(135, 750, {.minSpeed=20});

    //move to goal
    chassis.moveToPose(12,-2, 135, 1000, {.forwards = false});
    lifter.set_value(true);
    rOut.set_value(false);
}

void BlueAccomdationT() {
    //set pose
    chassis.setPose(48,0,0);
    loader.set_value(true);
    lifter.set_value(false);
    lOut.set_value(true);
    rOut.set_value(true);

    //move to goal
    chassis.moveToPose(36,48, 325,1000);
    
    //collect the two balls underneath the long goal
    chassis.moveToPose(15,12,225,1000,{.lead = 0.3});
    intake.move(127);
    pros::delay(1000);

    //move back
    chassis.moveToPose(15,30, 225, 1000,{.forwards = false});

    //move to the long goal
    chassis.moveToPose(24,0,150,1000);

    //turn to long goal and score
    lifter.set_value(true);
    lOut.set_value(true);
    rOut.set_value(false);
    chassis.moveToPose(3,-5,250, 1000,{.lead = 0.3, .minSpeed = 50});

}

void BlueSide() {

    //set pose
    chassis.setPose(48,0,0);
    loader.set_value(true);
    lifter.set_value(false);
    lOut.set_value(true);
    rOut.set_value(true);
    
     //move to loader
    chassis.moveToPose(72,-48,0,1000,{.lead = 0.3});
    intake.move(127);
    pros::delay(500);
    loader.set_value(true);
    lifter.set_value(true);
    lOut.set_value(true);
    rOut.set_value(true);
    chassis.waitUntilDone();
    pros::delay(750);

    //move to long goal
    chassis.moveToPose(24,-48,180,1000, {.forwards = false});
    chassis.waitUntil(2);
    loader.set_value(false);
    chassis.waitUntilDone();
    lOut.set_value(false);
    rOut.set_value(true);
    pros::delay(1250);

    //move back
    chassis.moveToPoint(36, -48, 100, {.minSpeed=40, .earlyExitRange=4});
    pros::delay(250);
    lifter.set_value(false);
    lOut.set_value(true);
    rOut.set_value(true);

    //move to pos to get to a good pos to get the 3 balls neat the top mid goal
    chassis.follow(MTTB_txt, 15, 1000);
    intake.move(127);

    //turn 180 to long goal
    chassis.turnToHeading(135,1000);
    
    //move to long goal and a bit forward
    chassis.moveToPose(12,-2, 135, 1000, {.forwards = false});
    lifter.set_value(true);
    rOut.set_value(false);

    chassis.moveToPose(12,-12, 135, 1000);
}
