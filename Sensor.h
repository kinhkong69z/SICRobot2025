#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <Arduino.h>
#include <HardwareSerial.h>

#define I2C_SDA 16 
#define I2C_SCL 17 
#define address1 0x30
#define address2 0x31
#define pinLox1 26
#define pinLox2 25

extern int IR[4];

extern VL53L0X_RangingMeasurementData_t measure1;
extern VL53L0X_RangingMeasurementData_t measure2;
extern int rightLaser;
extern int frontLaser;
extern Adafruit_VL53L0X lox1;
extern Adafruit_VL53L0X lox2;

extern int initLaser();
void initSerial();
void initImu();

void readLaserValue();
void readIrValue();
void readImuValue();

