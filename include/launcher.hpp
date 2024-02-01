#pragma once
#include "main.hpp"
#include <thread>
#define LAUNCHERSPEED 100
// NOLINTBEGIN
vex::motor _launcherMotor4(4);
vex::motor _launcherMotor5(5, true);
vex::motor_group launcherMotors(_launcherMotor4, _launcherMotor5);
volatile bool areLaunching = false;
inline int launchLoop();
vex::thread laucnherThread;
// NOLINTEND
inline void initLaunch() {
  laucnherThread = vex::thread(launchLoop);
  launcherMotors.setVelocity(0, vex::percentUnits::pct);
  launcherMotors.spin(vex::fwd);
}
inline int launchLoop() {
  for (;;) {
    if (areLaunching) {
      launcherMotors.setVelocity(100, vex::pct);
      launcherMotors.spinFor(360, vex::deg);
      launcherMotors.setVelocity(0, vex::pct);
      launcherMotors.stop(vex::brakeType::coast);
      vex::this_thread::sleep_for(1000);
    } else {
      vex::this_thread::sleep_for(500);
    }
  }
  return 1;
}
inline void toggleLaunch() { areLaunching = !areLaunching; }

inline void killLaunch() {
  areLaunching = false;
  launcherMotors.setVelocity(0, vex::percentUnits::pct);
  launcherMotors.stop(vex::brakeType::coast);
}