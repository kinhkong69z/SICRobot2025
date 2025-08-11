#include "Adafruit_VL53L0X.h"

#define I2C_SDA 33
#define I2C_SCL 32 
#define address1 0x30 // front
#define address2 0x32 // right
#define pinLox1 5  // front
#define pinLox2 17 // right

extern int IR[4];

extern VL53L0X_RangingMeasurementData_t measure1;
extern VL53L0X_RangingMeasurementData_t measure2;
extern int rightLaser;
extern int frontLaser;
extern Adafruit_VL53L0X lox1;
extern Adafruit_VL53L0X lox2;

void initLaser();
void initImu();

void readLaserValue();
void readIrValue();
void readImuValue();

