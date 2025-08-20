#include "Algorithm.h"
#include "mpu.h"

void setMotor(int left, int right) {
  SerialPort.print("#VEL 1 "); SerialPort.println(left);
  SerialPort.print("#VEL 2 "); SerialPort.println(right);
}
int rightWallCheck() {
  if (rightLaser > rightWallSet + 30) return rightLaser - rightWallSet;
  else if (rightLaser < rightWallSet - 30) return rightWallSet - rightLaser;
}

int frontWallCheck() {
  return frontLaser - frontWallSet;
}

