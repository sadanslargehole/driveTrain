/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       meyer                                                     */
/*    Created:      12/7/2023, 2:48:21 PM                                     */
/*    Description:  EXP project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <cstdlib>
#include "driveTrain.hpp"
#include "main.hpp"
#include "launcher.hpp"
#include "wings.hpp"
// A global instance of vex::brain used for printing to the EXP brain screen
vex::brain myBrain;
vex::controller myController;

int updateHUD()
{
    while (1)
    {
        // print controller values
        auto lv = myController.Axis3.position();
        auto rv = myController.Axis2.position();
        // bool for motor toggle
        // speed int
        myController.Screen.setCursor(0, 0);
        myController.Screen.clearScreen();
        myController.Screen.print("TEST MODE Right:%dIsOn:%s", rv, getCanMove() ? "true" : "false");
        myController.Screen.newLine();
        myController.Screen.print("Left:%dSpeed:1/%d", lv, getSpeed());
        vex::this_thread::sleep_for(500);
    }
    // if we get here we are having a bad day
    return -1;
}
int main()
{
    initWings();
    initDriveTrain();
    vex::thread controllerUpdateLoop(updateHUD);
    myController.Axis2.changed(rightStickChanged);
    myController.Axis3.changed(leftStickChanged);
    myController.ButtonB.pressed(toggleBrake);
    myController.ButtonA.pressed(resetAll);
    //init launcher
    initLaunch();
    myController.ButtonUp.pressed(toggleLaunch);
    myController.ButtonX.pressed(testAuto);

}
