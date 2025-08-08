#include "Algorithm.h"

int rightWallCheck() {
  if(rightLaser > rightWallSet + 30) return rightLaser - rightWallSet;
  else if(rightLaser < rightWallSet - 30) return rightWallSet - rightLaser;
}

int frontWallCheck() {
  return frontLaser - frontWallSet;
}