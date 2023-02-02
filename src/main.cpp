/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GPS21                gps           21              
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
  GPSSensor.setLocation(-1.5, -1.14, mm, 270, degrees);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void driveForward(int distance){
  frontLeftDrive.spinFor(forward, distance, degrees);
  frontRightDrive.spinFor(reverse, distance, degrees);
  backLeftDrive.spinFor(forward, distance, degrees);
  backRightDrive.spinFor(reverse, distance, degrees);
}
void driveReverse(int distance){
  frontLeftDrive.spinFor(reverse, distance, degrees);
  frontRightDrive.spinFor(forward, distance, degrees);
  backLeftDrive.spinFor(reverse, distance, degrees);
  backRightDrive.spinFor(forward, distance, degrees);
}
void turnRight(){
  frontLeftDrive.spinFor(forward, 180, degrees);
  frontRightDrive.spinFor(reverse, 180, degrees);
}
void turnLeft(){
  frontLeftDrive.spinFor(reverse, 180, degrees);
  frontRightDrive.spinFor(forward, 180, degrees);
}

void turnRoller(int amount){
  conveyorMotor.spinFor(forward, amount, degrees);
}


bool launchControl = false;

void launcher (){
  if (controller1.ButtonL1.pressing()){
    launchControl = true;
  }
  if (controller1.ButtonL2.pressing()){
    launchControl = false;
  }
  if (launchControl){
    launcherR.spin(reverse, 80,velocityUnits::pct);
    launcherL.spin(forward, 100,velocityUnits::pct);
  }
  if(!launchControl){
    launcherR.stop();
    launcherL.stop();
  }
}

void autoSkill(){
  expandMotor.spin(reverse);
}
void normalAutonomous(){
  driveForward(180);
  conveyorMotor.spinFor(forward, 270, degrees);
}

void autonomous(void) {

  //normalAutonomous();
  autoSkill();

  //dont chenge this!!
  Brain.resetTimer();
  while(1){
    if(Brain.Timer.value()<3){
      //adjust either the time or the motor power
      conveyorMotor.spin(forward, 30, pct);
    }
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                 5                          */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


int conveyor = 0;

void conveyorStart (){
  if (controller1.ButtonR1.pressing()){
    conveyor =  1;
  }
  if(controller1.ButtonR2.pressing()){
    conveyor = 0;
  }
  if(controller1.ButtonDown.pressing()){
    conveyor = -1;
  }
}

void conveyorControl(){
  conveyorStart();
  if (conveyor ==  1) {
    conveyorMotor.spin(vex::forward, 100, velocityUnits::pct);
  }
  else if (conveyor ==  0){
    if (controller1.ButtonB.pressing()){
      conveyorMotor.spin(forward, 50, pct);
    }
    else if (controller1.ButtonA.pressing()) {
      conveyorMotor.spin(reverse, 50, pct);
    }
    else{
      conveyorMotor.stop();
    }
  }
  else if (conveyor ==  -1){
    conveyorMotor.spin(vex::reverse, 100, velocityUnits::pct);
  }
}

void rollerControl (int i){
 rollerMotor.spin(vex::reverse, 50 * i, velocityUnits::pct);
}

//allows for forward and reverse control of the roller
void rollerThing(){ 
  if(controller1.ButtonA.pressing()){
    rollerControl(1);
  }
  if(controller1.ButtonB.pressing()){
    rollerControl(-1);
  }
  else{
    rollerMotor.stop();
  }
}

//prints to the brain
void printDrive (int input, int another){
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print(input);
  Brain.Screen.setCursor(1,32);
  Brain.Screen.print(another);
}

// void drivecontrol (){
//   int axis3 = controller1.Axis3.position();
//   int axis4 = controller1.Axis4.position();
//   int leftOutput = axis4 + axis3;
//   int rightOutput = axis4 - axis3;

//   leftDrive.spin(vex::forward, leftOutput , vex::percent);
//   rightDrive.spin(vex::forward, rightOutput , vex::percent);
//   rightOutput = rightOutput * -1;
//   printDrive(leftOutput, rightOutput);
// }

void getLocation()
{
  float x = GPSSensor.xPosition(mm) / 1000;
  float y = GPSSensor.yPosition(mm) / 1000;
  float z = GPSSensor.heading();



  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("X value = ");
  Brain.Screen.print(x);
  Brain.Screen.setCursor(45, 1);
  Brain.Screen.print("Y value = ");
  Brain.Screen.print(y);
  Brain.Screen.setCursor(23, 23);
  Brain.Screen.print("Rotation = ");
  Brain.Screen.print(z);
}

void crazyIdea (int xvalue, int yvalue){
 double T = atan(yvalue/xvalue);
 int z = GPSSensor.heading();

 double axis3 = 100 * sin(T - z);
 double axis4 = 100 * cos(T - z);
 double axis1 = 0;
  int frontRightWheel = axis3 - axis4 - axis1;
  int frontLeftWheel = axis3 + axis4 + axis1;
  int backRightWheel = axis3 + axis4 - axis1;
  int backLeftWheel = axis3 - axis4 + axis1;

  frontLeftDrive.spin(vex::forward, frontLeftWheel, vex::percent);
  backLeftDrive.spin(vex::forward, backLeftWheel, vex::percent);
  frontRightDrive.spin(vex::reverse, frontRightWheel, vex::percent);
  backRightDrive.spin(vex::reverse, backRightWheel, vex::percent);
}

void expand (){
  if(controller1.ButtonUp.pressing()){
    expandMotor.spin(reverse, 100, pct);
  }
  else {
    expandMotor.stop();
  }
}

void mechaniumWheels(){
  int axis1 = controller1.Axis1.position();
  int axis3 = controller1.Axis3.position();
  int axis4 = controller1.Axis4.position();
  
  int backLeftWheel = axis3 - axis4 - axis1; //fr
  int backRightWheel = axis3 + axis4 + axis1; //fl
  int frontLeftWheel = axis3 + axis4 - axis1; //br
  int frontRightWheel = axis3 - axis4 + axis1; //bl

  frontLeftDrive.spin(vex::reverse, frontLeftWheel, vex::percent);
  backLeftDrive.spin(vex::reverse, backLeftWheel, vex::percent);
  frontRightDrive.spin(vex::forward, frontRightWheel, vex::percent);
  backRightDrive.spin(vex::forward, backRightWheel, vex::percent);
}

void acklenNator (){
  float x = -1 * (GPSSensor.xPosition(mm) -  1550);
  float wheelSpeed = (100 * (x/3100));
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print(" Distance from wall= ");
  Brain.Screen.print(x);
  Brain.Screen.print(" speed= ");
  Brain.Screen.print(wheelSpeed);
  if (controller1.ButtonA.pressing()){
    frontLeftDrive.spin(vex::forward, wheelSpeed, vex::percent);
    backLeftDrive.spin(vex::forward, wheelSpeed, vex::percent);
    frontRightDrive.spin(vex::reverse, wheelSpeed, vex::percent);
    backRightDrive.spin(vex::reverse, wheelSpeed, vex::percent);
  }
  if (controller1.ButtonR1.pressing()){
    crazyIdea(0,0);
  }
  else{
   mechaniumWheels();
  }
}


void displayWheels (){
  int axis1 = controller1.Axis1.position();
  int axis3 = controller1.Axis3.position();
  int axis4 = controller1.Axis4.position();

  int frontRightWheel = axis3 - axis4 - axis1;
  int frontLeftWheel = axis3 + axis4 + axis1;
  int backRightWheel = axis3 + axis4 - axis1;
  int backLeftWheel = axis3 - axis4 + axis1;

  Brain.Screen.clearScreen();
  
  Brain.Screen.print("Front right Wheel: ");
  Brain.Screen.print(frontRightWheel);
  Brain.Screen.print(" Front left Wheel: ");
  Brain.Screen.print(frontLeftWheel);
  Brain.Screen.print(" Back right Wheel: ");
  Brain.Screen.print(backRightWheel);
  Brain.Screen.print(" Back left Wheel: ");
  Brain.Screen.print(backLeftWheel);
}



void robotTurn (int v){
  frontLeftDrive.spin(vex::forward, v, vex::percent);
  backLeftDrive.spin(vex::forward, v, vex::percent);
  frontRightDrive.spin(vex::reverse, -v, vex::percent);
  backRightDrive.spin(vex::reverse, -v, vex::percent);
}

void robotAdvance (int v){
  frontLeftDrive.spin(vex::forward, v, vex::percent);
  backLeftDrive.spin(vex::forward, v, vex::percent);
  frontRightDrive.spin(vex::reverse, v, vex::percent);
  backRightDrive.spin(vex::reverse, v, vex::percent);
}

float numberAdjust (float deg){
  if (deg > 360){
    deg =  deg -  360;
  }
  else if (deg < 0){
    deg = deg + 360;
  }
  return deg;
}


//x= -1.12 y= -1.27 for one of the rollers
//right is 1 left is 0
bool isTurningRight = 1;
float turnSpeed = 50;
float margin = 45;

void posisioning (float target){
  float x = GPSSensor.xPosition(mm);
  float y = GPSSensor.yPosition(mm);
  float z = GPSSensor.heading();
  
  controller1.Screen.clearScreen();
  controller1.Screen.setCursor(1,1);
  controller1.Screen.print("Heading: ");
  controller1.Screen.print(z);
  controller1.Screen.setCursor(2,1);
  controller1.Screen.print("Logic: ");
  if (z > numberAdjust(target + margin) && z < numberAdjust(target + 180)){
    controller1.Screen.print(numberAdjust(target + margin));
    controller1.Screen.print(" < ");
    controller1.Screen.print(z);
    controller1.Screen.print(" < ");
    controller1.Screen.print(numberAdjust(target + 180));
    controller1.Screen.setCursor(3,1);
    controller1.Screen.print("Turning Left");
  }
  else if (z <= numberAdjust(target + margin) && z > numberAdjust(target + 180)){
    controller1.Screen.print(numberAdjust(target + margin));
    controller1.Screen.print(" < ");
    controller1.Screen.print(z);
    controller1.Screen.print(" < ");
    controller1.Screen.print(numberAdjust(target + 180));
    controller1.Screen.setCursor(3,1);
    controller1.Screen.print("Turning Right");
  }

  Brain.Screen.setCursor(1,1);
  Brain.Screen.clearScreen();
  Brain.Screen.print("x = ");
  Brain.Screen.print(x);
  Brain.Screen.print("y = ");
  Brain.Screen.print(y);
  Brain.Screen.print("turn = ");
  Brain.Screen.print(z);


  if(isTurningRight == 1){  
    Brain.Screen.print("Turn Right");
    robotTurn(turnSpeed);
    if(z > numberAdjust(target + margin) && z < numberAdjust(target + 180)){
      Brain.Screen.print("Reversing");
      isTurningRight = 0;
      turnSpeed = turnSpeed * .5;
      margin = margin * .5;
    }
  }
  else{
    Brain.Screen.print("Turn Left");
    robotTurn(-1 * turnSpeed);
    if(z <= numberAdjust(target - margin) && z > numberAdjust(target + 180)){
      Brain.Screen.print("Reversing");
      isTurningRight = 1;
      turnSpeed = turnSpeed * .5;
      margin = margin * .5;
    }
  }
  controller1.Screen.setCursor(4,1);
  controller1.Screen.print(turnSpeed);

}

void screenDisplay(){
  int x = GPSSensor.xPosition(mm);
  int y = GPSSensor.yPosition(mm);
  int Rotation = GPSSensor.heading();

  controller1.Screen.clearScreen();
  controller1.Screen.setCursor(1,1);
  controller1.Screen.print("x= ");
  controller1.Screen.print(x);
  controller1.Screen.setCursor(2,1);
  controller1.Screen.print("y= ");
  controller1.Screen.print(y);
  controller1.Screen.setCursor(3,1);
  controller1.Screen.print("Rotation= ");
  controller1.Screen.print(Rotation);
}


void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    conveyorControl(); //intake
    launcher(); //output launcher
    mechaniumWheels(); //drivecontrol
    expand(); //Expander

    //rollerThing();//roller
    //getLocation();
    //posisioning(180);
    //acklenNator(); //drivercontrol
    //screenDisplay();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


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
