#include <Arduino.h>
#include "Sensor.h"

#define rightWallSet 100
#define frontWallSet 100

extern int rightWallCheck();
extern int frontWallCheck();
extern int irCheck();

void goToHill();
void inHill();
void goToConer();
void goToFrontWall();
void takeBall();
void goBack();