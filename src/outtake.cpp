#include "outtake.hpp"
#include "RobotConfig.hpp"
#include "pros/rtos.hpp"

bool loading = false;
int convSpeed = 0;
int t = 0;
void conveyor(void* param){
    while(true){
        outake.move(convSpeed);

        if((std::abs(outake.get_actual_velocity())<5&&convSpeed!=0)||(loading&&std::abs(intake.get_actual_velocity())<10&&convSpeed!=0)){
            t++;
        }else{
            t=0;
        }


        if(t>=7){ //if the outake is stuck for more than 0.15s
            t=0;
            outake.move(-convSpeed);
            pros::delay(150);
            outake.move(convSpeed);
            pros::delay(150); 
        }
        pros::delay(20);
    }
}