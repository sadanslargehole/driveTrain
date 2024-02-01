#pragma once
#include <thread>
#include <vex.h>
#include "main.hpp"
static vex::motor rightWing(8, true);
static vex::motor leftWing(1);
inline int rightBumper();
inline int leftBumper();
inline int rightTrigger();
inline int leftTrigger();
static vex::thread lb;
static vex::thread rb;
static vex::thread lt;
static vex::thread rt;

/**
* Cailbrates the wings
* THEY MUST BE COMPLETELY RETRACTED
*/

inline void initWings(){
    lb = vex::thread(leftBumper);
    rb = vex::thread(rightBumper);
    lt = vex::thread(leftTrigger);
    rt = vex::thread(rightTrigger);
    rightWing.resetPosition();
    leftWing.resetPosition();
    rightWing.setVelocity(0, vex::pct);
    leftWing.setVelocity(0, vex::pct);
    leftWing.spin(vex::forward);
    rightWing.spin(vex::forward);
}
inline void killWings(){
    leftWing.stop();
    rightWing.stop();
}
inline int rightBumper(){
    while(true){
        while (myController.ButtonR1.pressing()) {
           rightWing.setVelocity(-35, vex::pct);
        }
        if (rightWing.velocity(vex::pct)<-1) {
        rightWing.setVelocity(0, vex::pct);
            
        }
        vex::this_thread::sleep_for(30);
    }
    return 1;
}
inline int rightTrigger(){
    while(true){
        while(myController.ButtonR2.pressing()){
            rightWing.setVelocity(35, vex::pct);
        }
        if (rightWing.velocity(vex::pct)>1){
            rightWing.setVelocity(0, vex::pct);
        }
        vex::this_thread::sleep_for(30);
    }
return 1;
}
inline int leftBumper(){
    while(true){
        while (myController.ButtonL1.pressing()) {
            leftWing.setVelocity(-35, vex::pct);
        }
        if(leftWing.velocity(vex::pct)<0){
            leftWing.setVelocity(0, vex::pct);
        }
        vex::this_thread::sleep_for(30);
    }
return 1;
}
inline int leftTrigger(){
    while(true){
        while (myController.ButtonL2.pressing()) {
            leftWing.setVelocity(35, vex::pct);
        }
        if(leftWing.velocity(vex::pct)>1){
            leftWing.setVelocity(0, vex::pct);
        }
        vex::this_thread::sleep_for(30);
    }
return 1;
}
inline void resetAll(){
    rightWing.spinToPosition(0, vex::deg, 50, vex::velocityUnits::pct, false);
    leftWing.spinToPosition(0, vex::deg, 50, vex::velocityUnits::pct, false);
    rightWing.setVelocity(0, vex::pct);
    leftWing.setVelocity(0, vex::pct);
}
inline void lockWings(){
    leftWing.spinToPosition(0, vex::deg);
    rightWing.spinToPosition(0, vex::deg);
    leftWing.stop(vex::brakeType::hold);
    rightWing.stop(vex::brakeType::hold);
}