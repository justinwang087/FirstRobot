#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "RobotConfig.hpp"
#include "autons.hpp"

void on_center_button() {

}


void screenTask(void* param){
    while (true){
        pros::lcd::print(3, "X: %f", chassis.getPose().x);
        pros::lcd::print(4, "Y: %f", chassis.getPose().y);
        pros::lcd::print(5, "Theta: %f", chassis.getPose().theta);
        pros::delay(20);

    }
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    lifter.set_value(true);
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // pros::Task screen_task([&](){
    //     while (true){
    //         pros::lcd::print(3, "X: %f", chassis.getPose().x);
    //         pros::lcd::print(4, "Y: %f", chassis.getPose().y);
    //         pros::lcd::print(5, "Theta: %f", chassis.getPose().theta);
    //         pros::delay(20);
    //     
    // });
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    pros::Task screen_task(screenTask, (void*)"PROS", TASK_PRIORITY_MAX, 
    TASK_STACK_DEPTH_DEFAULT, "Screen Task");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    BlueAwp();
    //BlueSide();
}


/**
 * Runs the `erator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
pros::Controller controller(pros::E_CONTROLLER_MASTER);

void opcontrol() {

    chassis.setPose(48,0,180);

    bool lifterS = true;
    bool loaderS = true;
    bool rightS = true;
    bool leftS = true;

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    outake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    // loop forever
    while (true) {
        // stick pos.
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake.move(127);
            outake.move(127);
		}
		else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake.move(-127);
            outake.move(-127);
		}
		else{
			intake.move(0);
            outake.move(0);
		}
		
        if(controller.get_digital(DIGITAL_R1)){
            lifterS=!lifterS;
            lifter.set_value(lifterS);
            //toggle raise and lower jar (lifter)
        }
        if(controller.get_digital(DIGITAL_R2)){
            loader.set_value(loaderS);
            //toggle scoopy (loader)
        }
        if(controller.get_digital(DIGITAL_X)){
            rOut.set_value(rightS);
            //hold right side open, default close
        }
        if(controller.get_digital(DIGITAL_A)){
            lOut.set_value(leftS);
            //hold left side open, default close
        }

		
        // drive
        chassis.arcade(leftY, -rightX);
        
        // delay 
        pros::delay(25);
    }
}
