#include "Sensor.h"
#include <HardwareSerial.h>

#define rightWallSet 100
#define frontWallSet 100

extern HardwareSerial SerialPort; // Use UART2

extern int rightWallCheck();
extern int frontWallCheck();
extern int irCheck();

void setMotor(int left, int right);
void goToHill();
void inHill();
void goToConer();
void goToFrontWall();
void takeBall();
void goBack();
