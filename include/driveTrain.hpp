#pragma once
#include "main.hpp"
#include "wings.hpp"
#include <functional>
#include <vex.h>

static bool canMove = false;
static bool lock = false;
static double speed = .5;
static vex::motor _l0(0);
static vex::motor _l11(11);
static vex::motor _r9(9, true);
static vex::motor _r19(19, true);
static vex::motor_group motorL(_l0, _l11);
static vex::motor_group motorR(_r9, _r19);
static vex::drivetrain mainAutoTrain(motorL, motorR);
inline void initDriveTrain() {
  motorL.setVelocity(0, vex::pct);
  motorR.setVelocity(0, vex::pct);
}
inline bool getCanMove() { return canMove; }
inline void brakeFunc() {
  motorL.setStopping(vex::brakeType::brake);
  motorR.setStopping(vex::brakeType::brake);
}
inline void leftStickChanged() {
  if (lock)
    return;
  if (!canMove)
    return;
  motorL.setVelocity(myController.Axis3.position() * speed,
                     vex::percentUnits::pct);
}
inline void rightStickChanged() {
  if (lock)
    return;
  if (!canMove)
    return;
  motorR.setVelocity(myController.Axis2.position() * speed,
                     vex::percentUnits::pct);
}
inline void toggleBrake() {
  if (lock)
    return;
  if (canMove) {
    brakeFunc();
  } else {
    motorL.spin(vex::directionType::fwd);
    motorR.spin(vex::directionType::fwd);
  }
  canMove = !canMove;
}
inline void zero() {
  motorL.setVelocity(0, vex::pct);
  motorR.setVelocity(0, vex::pct);
}
inline void turnDeg(double deg) {
  lock = true;
  zero();
  mainAutoTrain.turnFor(vex::right, deg, vex::deg, true);
  lock = false;
}

inline double getSpeed() { return speed; }
inline void testAuto() {
    lockWings();
    zero();
    canMove = false;
    lock = true;
    motorL.stop();
    motorR.stop();
    motorL.setVelocity(SPEEDAUTO, vex::pct);
    motorR.setVelocity(SPEEDAUTO, vex::pct);
  motorL.spinFor(FIRST_MOVE_DISTANCE, vex::rotationUnits::deg, false);
  motorR.spinFor(FIRST_MOVE_DISTANCE, vex::rotationUnits::deg, true);

  motorL.spinFor(FIRST_TURN_DEGREE, vex::rotationUnits::deg, false);
  motorR.spinFor(-FIRST_TURN_DEGREE, vex::rotationUnits::deg, true);

  motorL.spinFor(SECOND_MOVE_DISTANCE, vex::rotationUnits::deg, false);
  motorR.spinFor(SECOND_MOVE_DISTANCE, vex::rotationUnits::deg, true);

  motorL.spinFor(SECOND_TURN_DEGREE, vex::rotationUnits::deg, false);
  motorR.spinFor(-SECOND_TURN_DEGREE, vex::rotationUnits::deg, true);

  motorL.spinFor(THIRD_MOVE_DISTANCE, vex::rotationUnits::deg, false);
  motorR.spinFor(THIRD_MOVE_DISTANCE, vex::rotationUnits::deg, true);

  motorL.spinFor(THIRD_TURN_DEGREE, vex::rotationUnits::deg, false);
  motorR.spinFor(-THIRD_TURN_DEGREE, vex::rotationUnits::deg, true);

  motorL.spinFor(FOURTH_MOVE_DISTANCE, vex::rotationUnits::deg, false);
  motorR.spinFor(FOURTH_MOVE_DISTANCE, vex::rotationUnits::deg, true);

  motorL.spinFor(FOURTH_TURN_DEGREE, vex::rotationUnits::deg, false);
  motorR.spinFor(-FOURTH_TURN_DEGREE, vex::rotationUnits::deg, true);

  motorL.spinFor(FIFTH_MOVE_DISTANCE, vex::rotationUnits::deg, false);
  motorR.spinFor(FIFTH_MOVE_DISTANCE, vex::rotationUnits::deg, true);

  motorL.spinFor(FIFTH_TURN_DEGREE, vex::rotationUnits::deg, false);
  motorR.spinFor(-FIFTH_TURN_DEGREE, vex::rotationUnits::deg, true);

  motorL.spinFor(SIXTH_MOVE_DISTANCE, vex::rotationUnits::deg, false);
  motorR.spinFor(SIXTH_MOVE_DISTANCE, vex::rotationUnits::deg, true);

  motorL.spinFor(SIXTH_TURN_DEGREE, vex::rotationUnits::deg, false);
  motorR.spinFor(-SIXTH_TURN_DEGREE, vex::rotationUnits::deg, true);

  motorL.spinFor(SEVENTH_MOVE_DISTANCE, vex::rotationUnits::deg, false);
  motorR.spinFor(SEVENTH_MOVE_DISTANCE, vex::rotationUnits::deg, true);

  motorL.spinFor(SEVENTH_TURN_DEGREE, vex::rotationUnits::deg, false);
  motorR.spinFor(-SEVENTH_TURN_DEGREE, vex::rotationUnits::deg, true);
}