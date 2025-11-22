#include "RobotConfig.hpp"
#include "api.h"

pros::MotorGroup left_motors ({-1, 2, 4}, pros::MotorGearset::blue);
pros::MotorGroup right_motors ({-1, 2, 4}, pros::MotorGearset::blue);
pros::adi::DigitalOut lifter('G');
pros::adi::DigitalOut lOut('A');
pros::adi::DigitalOut rOut('B');
pros::adi::DigitalOut loader('C');