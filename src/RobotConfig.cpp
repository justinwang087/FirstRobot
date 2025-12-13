#include "RobotConfig.hpp"
#include "api.h"

pros::MotorGroup right_motors ({-1, 2, 4}, pros::MotorGearset::blue);
pros::MotorGroup left_motors ({-7,8,-10}, pros::MotorGearset::blue);
pros::adi::DigitalOut lifter('D');
pros::adi::DigitalOut Out('G');
pros::adi::DigitalOut loader('A');
pros::adi::DigitalOut descore('C');
pros::Motor intake(3); //intake
pros::Motor outake(9); //outake


//pros::Rotation verticalEnc(7);
//lemlib::TrackingWheel vertical(&verticalEnc, lemlib:: Omniwheel::NEW_2, +2);

//pros::Rotation horizontalEnc(8);
//lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib:: Omniwheel::NEW_2, +6);
// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              10.25, // 10.25 inch track width
                              lemlib::Omniwheel::NEW_325, 
                              360, // drivetrain rpm is 360
                              8 // horizontal drift is 2 (for now)
);

pros::Imu imu(6);
lemlib::OdomSensors sensors(
                            nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              8, // derivative gain (kD)
                                              0, // anti windup
                                              1, // small error range, in inches
                                              120, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              750, // large error range timeout, in milliseconds
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
                                  25, // minimum output where drivetrain will move out of 127
                                  1.125 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);
