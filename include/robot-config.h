using namespace vex;

extern brain Brain;

// VEXcode devices

extern controller controller1;

extern motor frontRightDrive;
extern motor frontLeftDrive;
extern motor backLeftDrive;
extern motor backRightDrive;

extern motor rollerMotor;

extern motor conveyorMotor;

extern motor launcherR;
extern motor launcherL;

extern motor expandMotor;

extern gps GPSSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );