#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller controller1; 

//these are the wheel motors (mechanum drive)
motor backRightDrive(PORT20); 
motor frontRightDrive(PORT18); 
motor frontLeftDrive(PORT1); 
motor backLeftDrive(PORT9); 

motor rollerMotor(PORT3); //roller motor?

motor conveyorMotor(PORT10); //conveyor motor (also intake)

motor launcherR(PORT16); //launcher right motor
motor launcherL(PORT15); //launcher left motor

motor expandMotor(PORT13); //expansion

gps GPSSensor = gps(PORT12, 0, 0, mm, 0);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}