#include "mpu.h"

float angleZ = 0.0;
unsigned long lastTime = 0;
int drift = 0;

void writeRegister(int addr, int reg, int data) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void readRegisters(int addr, int reg, int count, int *data) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, count);
  for (int i = 0; i < count; i++) {
    data[i] = Wire.read();
  }
}

void calibrateGyro() {
  writeRegister(MPU9250_ADDR, GYRO_CONFIG, 0x00);
  for (int i = 0; i < 1000; i++) {
    int buf[6];
    readRegisters(MPU9250_ADDR, GYRO_XOUT_H, 6, buf);
    int gz_raw = (buf[4] << 8) | buf[5];
    drift += gz_raw;
  }
  drift /= 1000;
}

void readAngle() {
  int buf[6];
  readRegisters(MPU9250_ADDR, GYRO_XOUT_H, 6, buf);

  int gz_raw = (buf[4] << 8) | buf[5] - drift;

  float gz_dps = (float)gz_raw / 131.0;

  long now = micros();
  float dt = (now - lastTime) / 1000000.0;
  lastTime = now;

  angleZ += gz_dps * dt;
  if (angleZ > 180.0) angleZ -= 360.0;
  if (angleZ < -180.0) angleZ += 360.0;
}