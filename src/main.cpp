#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "RobotConfig.hpp"


pros::Motor intake(3); //intake
pros::Motor outake(9); //outake
pros::adi::DigitalOut lifter('G');
pros::adi::DigitalOut lOut('A');
pros::adi::DigitalOut rOut('B');
pros::adi::DigitalOut loader('C');


pros::Rotation verticalEnc(7);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib:: Omniwheel::NEW_2, +2);

pros::Rotation horizontalEnc(8);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib:: Omniwheel::NEW_2, +6);
// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              11, // 10.25 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              600, // drivetrain rpm is 360
                              8 // horizontal drift is 2 (for now)
);

pros::Imu imu(7);
lemlib::OdomSensors sensors(
                            &vertical, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(7.8, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              41, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(4.2679981, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              33.2261, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);

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
	pros::lcd::print(1, "justin is a goober");
    //chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    //chassis.setPose(51.064,1.31,-57.72);
    //intake.move(127);
    //chassis.moveToPoint(18,  23, 1000, {.minSpeed = 75});
    //pros::delay(1000);
    //chassis.turnToHeading(-170,1000);
    //chassis.moveToPoint(15 ,8, 1000);
   // pros::delay(1000);
    //intake.move(-127);
    //chassis.moveToPoint(22,  20, 1000, {.forwards = false})
    //chassis.turnToHeading(-184, 1000);
    //pros::delay(2000);
    //chassis.moveToPose(24, -48, 180, 1000, {.lead = 2, .minSpeed = 75});
   
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

    chassis.setPose(48,24, 0);
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
			
		
        // drive
        chassis.arcade(leftY, -rightX);
        
        // delay 
        pros::delay(25);
    }
}
