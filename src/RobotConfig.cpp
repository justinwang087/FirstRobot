#include "RobotConfig.hpp"
#include "api.h"
#include "lemlib/chassis/trackingWheel.hpp"

pros::MotorGroup right_motors ({-1, 4, 6}, pros::MotorGearset::blue);
pros::MotorGroup left_motors ({-5,7,-8}, pros::MotorGearset::blue);
pros::adi::DigitalOut loader('C');
pros::adi::DigitalOut descore('F');
pros::Rotation horizontal_sensor (11);
pros::Rotation vertical_sensor (-17);
pros::Imu imu(3);
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_sensor, lemlib::Omniwheel::NEW_2, -7.086864948);
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_sensor, lemlib::Omniwheel::NEW_2, -0.05695700685);

pros::Motor intake(10); 
pros::Motor outake(9); //outake


lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              10.25, // 10.25 inch track width
                              lemlib::Omniwheel::NEW_325, 
                              360, // drivetrain rpm is 360
                              8 // horizontal drift is 2 (for now)
);


// lateral PID controller
lemlib::ControllerSettings lateral_controller(6.6, // proportional gain (kP)                                    //10
                                              0, // integral gain (kI)
                                              5.5, // derivative gain (kD)                                        //8
                                              0, // anti windup
                                              1, // small error range, in inches                        //1
                                              120, // small error range timeout, in milliseconds //120
                                              3, // large error range, in inches                        //3
                                              750, // large error range timeout, in milliseconds //750
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2.62, // proportional gain (kP)                  //4.2679981
                                              0, // integral gain (kI)
                                              16.75, // derivative gain (kD)                              //33.2261
                                              0, // anti windup
                                              1, // small error range, in degrees                           //1
                                              150, // small error range timeout, in milliseconds    //150
                                              3, // large error range, in degrees                          //3
                                              650, // large error range timeout, in milliseconds    //650
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
