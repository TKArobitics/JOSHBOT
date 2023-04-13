#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1;

//I apologize for spinny thing but here they only have one spinny thing that is not a wheel 

motor frontRightMotor(PORT6);
motor frontLeftMotor(PORT1);
motor backLeftMotor(PORT11);
motor backRightMotor(PORT20);
motor rollerMotor(PORT8);
motor rollerMotor2(PORT7);
motor extension(PORT13);
motor extension2(PORT14);


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}