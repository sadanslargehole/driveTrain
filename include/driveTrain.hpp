#pragma once
#include <vex.h>
#include "main.hpp"
#include <functional>

static bool canMove = false;
static bool lock = false;
static double speed = .5; 
static vex::motor _l0(0);
static vex::motor _l10(10);
static vex::motor _l11(11);
static vex::motor _r9(9, true);
static vex::motor _r18(18, true);
static vex::motor _r19(19, true);
static vex::motor_group motorL(_l0, _l10, _l11);
static vex::motor_group motorR(_r9, _r18, _r19);
static vex::drivetrain mainAutoTrain(motorL, motorR);
inline void initDriveTrain(){
    motorL.setVelocity(0, vex::pct);
    motorR.setVelocity(0,vex::pct);
}
inline bool getCanMove(){
    return canMove;
}
inline void brake()
{
    motorL.setStopping(vex::brakeType::brake);
    motorR.setStopping(vex::brakeType::brake);
}
inline void leftStickChanged()
{
    if (lock)
        return;
    if (!canMove)
        return;
    motorL.setVelocity(myController.Axis3.position()*speed, vex::percentUnits::pct);
}
inline void rightStickChanged()
{
    if (lock)
        return;
    if (!canMove)
        return;
    motorR.setVelocity(myController.Axis2.position()*speed, vex::percentUnits::pct);
}
inline void toggleBrake()
{
    if (lock)
        return;
    if (canMove)
    {
        brake();
    }
    else
    {
        motorL.spin(vex::directionType::fwd);
        motorR.spin(vex::directionType::fwd);
    }
    canMove = !canMove;
}
inline void zero(){
    motorL.setVelocity(0, vex::pct);
    motorR.setVelocity(0, vex::pct);
}
inline void turnDeg(double deg)
{
    lock = true;
    zero();
    mainAutoTrain.turnFor(deg, vex::deg, true);
    lock = false;
}

inline double getSpeed()
{
    return speed;
}
