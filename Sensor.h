#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <Arduino.h>

#define I2C_SDA 33 // Example: GPIO4 for SDA
#define I2C_SCL 32 // Example: GPIO5 for SCL
#define address1 0x30
#define address2 0x31
#define pinLox1 26
#define pinLox2 25

extern int IR[4];

extern VL53L0X_RangingMeasurementData_t measure1;
extern VL53L0X_RangingMeasurementData_t measure2;
extern int dataLox1;
extern int dataLox2;
extern Adafruit_VL53L0X lox1;
extern Adafruit_VL53L0X lox2;

extern int initLaser();

void readLaserValue();
void readIRValue();

