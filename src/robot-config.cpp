#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller controller1;

using signature = vision::signature;
using code = vision::code;

//I apologize for spinny thing but here they only have one spinny thing that is not a wheel 

motor frontRightMotor(PORT6);
motor frontLeftMotor(PORT1);
motor backLeftMotor(PORT11);
motor backRightMotor(PORT20);
motor rollerMotor(PORT8);
motor rollerMotor2(PORT7);
motor extension(PORT13);
motor extension2(PORT14);

signature colorSensor__REDSIDE = signature (1, 6781, 8753, 7768, -837, -219, -528, 2.100, 0);
signature colorSensor__BLUESIDE = signature (2, -2849, -2239, -2544, 10593, 12529, 11562, 2.500, 0);
vision colorSensor = vision (PORT11, 50, colorSensor__REDSIDE, colorSensor__BLUESIDE);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}