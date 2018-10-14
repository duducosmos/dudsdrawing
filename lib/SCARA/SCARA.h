#include <Arduino.h>
#include <Servo.h>
#include <math.h>


#ifndef SCARA_H
#define SCARA_H

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
         |    A  B     |
          --------------
          Origin in A, alpha is Servo A angle.
          Beta is Servo B angle.
         */
        float AB;
        float AC;
        float BD;
        float DE;
        float CE;
        float EX;
        float XEC;
        float pi;
        float omega;
};

struct Servos_Angle {
    int left;
    int right;
};

class SCARA {

private:
    ArmPoints armpoints;

    Servo servo_left;
    Servo servo_right;

    float gamma(float alpha, float beta);
    float delta(float alpha, float beta);
    float _dx();

public:

    SCARA(Servo servoLeft, Servo servoRight, ArmPoints arm_points);

    Servos_Angle angles(float x, float y);

    float get_x(float alpha, float beta);
    float get_y(float alpha, float beta);
    float get_alpha(float x, float y);
    float get_beta(float x, float y);
    void move(float x, float y);


};


#endif
