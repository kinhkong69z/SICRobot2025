#include <Wire.h>
#include <Arduino.h>

#define MPU9250_ADDR   0x68
#define PWR_MGMT_1     0x6B
#define GYRO_XOUT_H    0x43
#define GYRO_CONFIG    0x1B

extern float angleZ;       // integrated yaw angle
extern unsigned long lastTime;
extern int drift;

void writeRegister(int addr, int reg, int data);
void readRegisters(int addr, int reg, int count, int *data);
void calibrateGyro();
void readAngle();