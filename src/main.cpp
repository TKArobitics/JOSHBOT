/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void expand(){
  extension.spin(reverse);
}

void setMotors(int prct){
  frontLeftMotor.setVelocity(prct, pct);
  backLeftMotor.setVelocity(prct, pct);
  frontRightMotor.setVelocity(prct, pct);
  backRightMotor.setVelocity(prct, pct);
}

void turnRoller(int dist){
  rollerMotor.spinFor(reverse, dist, degrees, false);
  rollerMotor2.spinFor(forward, dist, degrees);
}

void turnRollerWhile(int dist){
  rollerMotor.spinFor(reverse, dist, degrees, false);
  rollerMotor2.spinFor(forward, dist, degrees, false);
}

void allForward(int dist){
  frontLeftMotor.spinFor(forward, dist, degrees, false);
  frontRightMotor.spinFor(reverse, dist, degrees, false);
  backRightMotor.spinFor(reverse, dist, degrees, false);
  backLeftMotor.spinFor(forward, dist, degrees);
}

void allForwardWhile(int dist){
  frontLeftMotor.spinFor(forward, dist, degrees, false);
  frontRightMotor.spinFor(reverse, dist, degrees, false);
  backRightMotor.spinFor(reverse, dist, degrees, false);
  backLeftMotor.spinFor(forward, dist, degrees, false);
}

void allStart(){
  frontLeftMotor.spin(forward);
  frontRightMotor.spin(reverse);
  backRightMotor.spin(reverse);
  backLeftMotor.spin(forward);
}

void allBrake(){
  frontLeftMotor.stop(brake);
  frontRightMotor.stop(brake);
  backRightMotor.stop(brake);
  backLeftMotor.stop(brake);
}

void backLeftPivot(float dist){
  frontLeftMotor.spinFor(reverse, dist, degrees, false);
  frontRightMotor.spinFor(forward, dist, degrees, false);
  backRightMotor.spinFor(forward, dist, degrees, false);
  backLeftMotor.spinFor(forward, dist, degrees);
}

void tankTurn(int dist){
  frontLeftMotor.spinFor(forward, dist, degrees, false);
  frontRightMotor.spinFor(forward, dist, degrees, false);
  backRightMotor.spinFor(forward, dist, degrees, false);
  backLeftMotor.spinFor(forward, dist, degrees);
}

void rightSideOnly(int dist){
  frontRightMotor.spinFor(reverse, dist, degrees, false);
  backRightMotor.spinFor(reverse, dist, degrees);
}

void safeSkills(){
  setMotors(5);
  allForwardWhile(360);
  turnRoller(200);
  expand();
}

void blueLong(){
  setMotors(5);
  allForwardWhile(-360);
  turnRoller(200);
  allForward(100);
  setMotors(50);
  tankTurn(-300);
  setMotors(75);
  allForward(2200);
  allForward(-2200);
}

// void blueShort(){
//   rightSideOnly();
//   setMotors();
//   allForwardWhile();
//   turnRoller();
//   rightSideOnly();
//   allForward();
// }

// void blueShort(){
//   rightSideOnly();
//   setMotors();
//   allForwardWhile();
//   turnRoller();
//   rightSideOnly();
//   allForward();
// }

// what does this do?
void skills (){
  // setMotors(25);
  // allForwardWhile(30);
  // turnRoller(100); 
  // setMotors(100);
  // allForward(-500);
  // tankTurn(625);
  // allForward(600);
  // setMotors(25);
  // allForwardWhile(30);
  // turnRoller(100);
  // setMotors(100);
  // allForward(125);
  // tankTurn(937);
  // allForward(2500);
  // tankTurn(312);
  // setMotors(25);
  // allForwardWhile(30);
  // turnRoller(100); 
  // setMotors(100);
  // allForward(-500);
  // tankTurn(625);
  // allForward(600);
  // setMotors(25);
  // allForwardWhile(30);
  // turnRoller(100);
  // expand();
  
  //(for 4/13/23)
  setMotors(5);
  allForwardWhile(-360);
  turnRoller(200);
  setMotors(50);
  allForward(2400);
  allForward(-1600);
  tankTurn(300);
  setMotors(10);
  allForwardWhile(150);
  turnRoller(200);
  setMotors(50);
  tankTurn(-150);
  allForward(2500);
  rightSideOnly(-500);

}

void rampUpSpeed(int startingSpeed, int targetSpeed){
  int currentSpeed = startingSpeed;
  while (startingSpeed < targetSpeed)
  {
    currentSpeed +=5;
    setMotors(currentSpeed);
    wait(.2, sec);
  }
}

void rampDownSpeed(int startingSpeed, int targetSpeed){
  int currentSpeed = startingSpeed;
  while (startingSpeed > targetSpeed)
  {
    currentSpeed -=5;
    setMotors(currentSpeed);
    wait(.2, sec);
  }
}

void testAuto(){ // purely for testing robot functionality (NOT FINAL CODE)
  rampUpSpeed(0,10);
  allForwardWhile(200);
  turnRoller(180);
  rampUpSpeed(10,50);
  allForward(-200);
  tankTurn(180);
  expand();
}

void guaranteedLongRoller(){
  allForwardWhile(100);
  turnRoller(600);
  allForward(-100);
}

void guaranteedShortRoller(){
  allForward(-800);
  tankTurn(240);
  
  setMotors(10);
  allForwardWhile(50);
  turnRollerWhile(900);
  allForward(50);

  // setMotors(30);
  // allForward(-200);
  // tankTurn(340);
  // setMotors(100);
  // allForward(-1000);
}



void autonomous(void) {
  // skills();
  // testAuto();
  // safeSkills();
  // // headToHead();

  // guaranteedLongRoller();
  guaranteedShortRoller();

  //  //this should move the robot forward
  // frontLeftMotor.spin(forward);
  // frontRightMotor.spin(reverse);
  // backLeftMotor.spin(forward);
  // backRightMotor.spin(reverse);

  // //this should rotate the roller motor
  // turnRoller(180);
  
  // //this should stop the roller motor
  // rollerMotor.stop();

  // ..........................................................................
  // Insert autonomous user code here.
  // .......................................................................... 
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//1 = tank drive, 0 = One Stick Drive
bool tankyDwive = 0;

void tankDrive (){
  int axis3 = controller1.Axis3.position();
  int axis2 = controller1.Axis2.position();

  frontLeftMotor.spin(vex::forward, axis3, vex::percent);
  frontRightMotor.spin(vex::reverse, axis2, vex::percent);
  backLeftMotor.spin(vex::forward, axis3, vex::percent);
  backRightMotor.spin(vex::reverse, axis2, vex::percent);
}

void oneStick (){
  int axis3 = controller1.Axis3.position();
  int axis2 = controller1.Axis4.position();
  frontLeftMotor.spin(vex::forward, axis3 + axis2, vex::percent);
  frontRightMotor.spin(vex::reverse, axis3 - axis2, vex::percent);
  backLeftMotor.spin(vex::forward, axis3 + axis2, vex::percent);
  backRightMotor.spin(vex::reverse, axis3 - axis2, vex::percent);
}


void drivecontrol (){
  if (tankyDwive == 1){
    tankDrive();
  }
 else{
    oneStick();
  }
}

void spinnyThingControl (int i){
 rollerMotor.spin(vex::reverse, 50 * i, velocityUnits::pct);
 rollerMotor2.spin(vex::forward, 50 * i, velocityUnits::pct);
}

void spinnyThing(){
  if(controller1.ButtonA.pressing()){
    spinnyThingControl(1);
  }
  else if(controller1.ButtonB.pressing()){
    spinnyThingControl(-1);
  }
  else{
    rollerMotor.stop();
    rollerMotor2.stop();
  }
}

void launcher (){
  if (controller1.ButtonRight.pressing()){
    extension.spin(forward, 100 ,pct);
  }
}



void matchstart(){
  skills();
  // allForwardWhile(100);
  // setMotors(100);
  // turnRoller(100);
  // backLeftPivot(520);
  // tankTurn(425);
  // allForward(600);
  // setMotors(25);
  // allForward(50);
  // turnRoller(-120);
}

void extensionControl(){
  if (controller1.ButtonL1.pressing()){
    expand();
  }
  else if (controller1.ButtonL2.pressing()) {
    extension.stop();
  }
}

void matchAutonomous(){
  if (controller1.ButtonLeft.pressing()){
    matchstart();
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  // matchstart();
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    launcher();
    drivecontrol();
    spinnyThing();
    extensionControl();

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
