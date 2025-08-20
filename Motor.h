#ifndef MOTOR_H   // include guard start
#define MOTOR_H

#include <Arduino.h>
#include "Sensor.h"

class Motor {
private: 
  int speed;
  int kP, kD;
  int idMotor;
public: 
  Motor() {}
  Motor(int idMotor) : idMotor(idMotor) {} 
  void setPID(int kP, int kD);
  void setMotor(int speed);
  void turnRight(int speed);
  void turnLeft(int speed);
  void turn180(int speed);
};
// extern Motor motorLeft(1);
// extern Motor motorRight(2);

#endif // MOTOR_H


