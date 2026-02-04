#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "outtake.hpp"
#include "pros/misc.h"
#include "RobotConfig.hpp"
#include "autons.hpp"
#include "outtake.hpp"
#include "pros/rtos.h"
#include <math.h>

pros::Task* screen_task = nullptr;
pros::Task* outake_task = nullptr;

void screenTask(void* param){
    while (true){
        pros::lcd::print(1, "X: %f", chassis.getPose().x);
        pros::lcd::print(2, "Y: %f", chassis.getPose().y);
        pros::lcd::print(3, "Theta: %f", chassis.getPose().theta);
        pros::lcd::print(4, "H: %.4f, V: %.4f",
            horizontal_sensor.get_position()*M_PI*lemlib::Omniwheel::NEW_2/(36000.0),   //distance traveled in inches
            vertical_sensor.get_position()*M_PI*lemlib::Omniwheel::NEW_2/(36000.0));    //distance traveled in inches

        pros::lcd::print(5, "deg: %f", imu.get_heading());
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
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    pros::Task screen_task([=](){
        while (true){
            lemlib::Pose pose = chassis.getPose();
            pros::lcd::print(1, "X: %f", pose.x);
            pros::lcd::print(2, "Y: %f", pose.y);
            pros::lcd::print(3, "Theta: %f", pose.theta);
            pros::lcd::print(4, "H: %.4f, V: %.4f",
                horizontal_sensor.get_position()*M_PI*lemlib::Omniwheel::NEW_2/(36000.0),   //distance traveled in inches
                vertical_sensor.get_position()*M_PI*lemlib::Omniwheel::NEW_2/(36000.0));    //distance traveled in inches

            pros::lcd::print(5, "deg: %f", imu.get_heading());
            pros::delay(100);
        }
    });
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    
    pros::Task outakxne_task(conveyor, (void*)"PROS", TASK_PRIORITY_DEFAULT, 
    TASK_STACK_DEPTH_DEFAULT, "Conveyor");
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
    skills();
}


/**
 * Runs the operator control code. This function will be started in its own task
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

    convSpeed=0;
    chassis.setPose(48,-24,0);

    bool loaderS = false;
    bool descoreS = false;
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    outake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    // loop forever
    while (true) {
        // stick pos.
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			convSpeed=127;

		}
		else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            convSpeed=-127;
		}
		else{
            convSpeed=0;
		}

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            outake.move(127);
        }
        else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            outake.move(-127); 
        }
        else {
            outake.move(0);
        }
		

        if(controller.get_digital_new_press(DIGITAL_B)){
            loaderS =!loaderS;
            loader.set_value(loaderS);
        }

        if (controller.get_digital_new_press(DIGITAL_A)) {
            descoreS = !descoreS;
            descore.set_value(descoreS);
            //toggle descore piston
        }

		
        // drive
        chassis.arcade(leftY, rightX);
        
        // delay 
        pros::delay(25);
    }
}
