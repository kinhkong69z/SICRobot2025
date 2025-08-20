#include "Adafruit_VL53L0X.h"
/*
  IR from left to right pin config {36, 39, 34, 35, 25, 26, 27}
*/
#define I2C_SDA 33
#define I2C_SCL 32 
#define address1 0x30 // front
#define address2 0x32 // right
#define pinLox1 12  // front
#define pinLox2 13 // right


extern int IR[7];
extern int irCalib[7];

extern VL53L0X_RangingMeasurementData_t measure1;
extern VL53L0X_RangingMeasurementData_t measure2;
extern int rightLaser;
extern int frontLaser;
extern Adafruit_VL53L0X lox1;
extern Adafruit_VL53L0X lox2;

void initLaser();
void initImu();

void calibIR();
void readLaserValue();
void readIrValue();
void readImuValue();
void servo(int angle);

