#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep 
#include "lemlib/chassis/chassis.hpp"
#include "pros/motor_group.hpp"
#include "pros/rotation.hpp"

extern pros::MotorGroup left_motors; //left motor group
extern pros::MotorGroup right_motors; //right motor group

extern pros::Motor intake; //intake
extern pros::Motor outake; //outake
extern pros::adi::DigitalOut lifter;
extern pros::adi::DigitalOut Out;
extern pros::adi::DigitalOut loader;
extern pros::adi::DigitalOut descore;
extern pros::Rotation horizontal_sensor;
extern pros::Rotation vertical_sensor;
extern pros::Imu imu;
    
extern lemlib::Drivetrain drivetrain;
extern lemlib::TrackingWheel vertical;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;
extern lemlib::Chassis chassis;