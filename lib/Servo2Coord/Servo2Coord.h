#include <Arduino.h>

#ifndef SERVO2COORD_H
#define SERVO2COORD_H

struct ArmPoints {
  /*
    A: Left Servo axis;
    B: Right servo axis;
    C: left joint;
    D: Right joint;
    E: Pen joint;
    X: Pen;
    O: origin

    -------------
    |      X      |
    |      E      |
    |   /     \   |
    |  /       \  |
    | C         D |
    |  \       /  |
    |   \     /   |
    |    A O B    |
    --------------
  */
  float AB;
  float AC;
  float CE;
  float EX;
  float XEC;
};

class Servo2Coord {
  /*
         Servo Values
     ----------------
    |               |
    |      1 1      |
    |      | |      |
    |      | |      |
    | O----A B----O |
     ---------------

       Axis
     --------
    |        |
    | y      |
    | |      |
    | |      |
    | O----x |
     --------

  */
  ArmPoints armpoints;
  float A_x, A_y;
  float B_x, B_y;
  


};


#endif
