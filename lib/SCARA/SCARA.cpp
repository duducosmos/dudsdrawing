#include <SCARA.h>

SCARA::SCARA(Servo servoLeft, Servo servoRight, ArmPoints arm_points):
            servo_left(servoLeft), servo_right(servoRight){
    armpoints = arm_points;

}

void SCARA::move(float x, float y){
    float _alpha = get_alpha(x, y);
    float _beta = get_beta(x, y);
    servo_left.write(_alpha);
    servo_right.write(_beta);
}

float SCARA::_dx(){
    float dx = armpoints.DE * armpoints.DE + armpoints.EX * armpoints.EX;
    dx = dx - 2 * armpoints.DE * armpoints.EX * cos(armpoints.pi - armpoints.omega);
    dx = sqrt(dx);
    return dx;

}

float SCARA::get_beta(float x, float y){
    float teta2c = y / (armpoints.AB - x);
    teta2c = atan(teta2c);
    float bx = armpoints.AB - x;
    bx = bx * bx + y * y;
    bx = sqrt(bx);
    float teta2d = bx * bx + armpoints.BD * armpoints.BD - _dx() * _dx();
    teta2d = teta2d / (2 * armpoints.BD * bx);

    float teta2 = teta2c + teta2d;
    return 180 - teta2;

}

float SCARA::get_alpha(float x, float y){
    float teta2 = 180 - get_beta(x, y);

    float y4 = y + armpoints.BD * sin(armpoints.pi - teta2);
    float x4 = x + armpoints.AB * _dx() * cos(armpoints.pi - teta2);

    float _delta = (x4 - x) / (y - y4);
    _delta = atan(_delta);

    float epslon = armpoints.EX * armpoints.EX + _dx() * _dx();
    epslon = epslon -  armpoints.DE * armpoints.DE;
    epslon = epslon / (2 * armpoints.BD * _dx());
    epslon = acos(epslon);

    float x1 = x + armpoints.EX * sin(_delta - epslon);
    float y1 = y - armpoints.EX * cos(_delta - epslon);

    float ae = sqrt(x1 * x1 + y1 * y1);

    float theta1A = y1 / x1;
    theta1A = atan(theta1A);

    float theta1B = ae + armpoints.AC - armpoints.CE;
    theta1B = theta1B / ( 2 * armpoints.AC * ae);
    theta1B = acos(theta1B);

    return theta1A + theta1B;
}

float SCARA::get_x(float alpha, float beta){
    float _delta = delta(alpha, beta);
    float _gamma = gamma(alpha, beta);
    float x = armpoints.AB * cos(alpha) + armpoints.CE * cos(_gamma + _delta);
    return x;
}

float SCARA::get_y(float alpha, float beta){
    float _delta = delta(alpha, beta);
    float _gamma = gamma(alpha, beta);
    float y = armpoints.AB * sin(alpha) + armpoints.CE * sin(_gamma + _delta);
    return y;
}

float SCARA::gamma(float alpha, float beta){
    float __x = armpoints.AB * (sin(beta) - sin(alpha));
    float __y = armpoints.AB + armpoints.AC * (cos(beta) - cos(alpha));
    return atan2(__x, __y);

}

float SCARA::delta(float alpha, float beta){
    float x0 = armpoints.AB + armpoints.AC * cos(beta) - armpoints.AC * cos(alpha);
    x0 = x0 * x0;
    float x1 = armpoints.AC * sin(beta) - armpoints.AC * sin(alpha);
    x1 = x1 * x1;

    x0 = x0 + x1;
    x0 = x0 / (2.0 * armpoints.CE);
    return acos(x0);
}
