#ifndef vex.h

#include "vex.h"
#endif

#include "main.h"

using namespace vex;

// turnRollerFromShortStart() will start in the short position and move in front of the roller to then spin it and then move away.
void turnRollerFromShortStart(){
    moveForwardWait(8);
    turnRight(9999);
    moveForwardWait(10);
    turnRight(9999);
    moveForwardWait(4);
    spinRollerWait();
    moveReverseWait(100);
}