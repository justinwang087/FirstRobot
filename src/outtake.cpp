#include "outtake.hpp"
#include "RobotConfig.hpp"
#include "pros/rtos.hpp"

bool loading = false;
int convSpeed = 0;
int prevConvSpeed = 0;
void conveyor(void* param){
    while(true){
        outake.move(convSpeed);
        if(prevConvSpeed!=convSpeed){
            pros::delay(250);
            prevConvSpeed = convSpeed;
        }else{
            pros::delay(100);

            if(std::abs(outake.get_actual_velocity())<5&&convSpeed!=0){
                outake.move(-convSpeed);
                pros::delay(150);
                outake.move(convSpeed);
                pros::delay(150);
            }
            if(loading&&std::abs(intake.get_actual_velocity())<10&&convSpeed!=0){
                intake.move(-convSpeed);
                pros::delay(150);
                intake.move(convSpeed);
                pros::delay(150);
            }
        }
    }
}