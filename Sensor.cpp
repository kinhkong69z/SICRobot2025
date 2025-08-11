#include "Sensor.h"
#include "esp32-hal.h"
#include "esp32-hal-adc.h"


int IR[4];
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
int rightLaser;
int frontLaser;

bool laser1_ok = false;
bool laser2_ok = false;

void initLaser() {
  // Tắt cả 2 cảm biến
  digitalWrite(pinLox1, LOW);
  digitalWrite(pinLox2, LOW);
  delay(10);

  // Bật cảm biến 1 trước
  digitalWrite(pinLox1, HIGH);
  digitalWrite(pinLox2, LOW);
  delay(10);
  
  lox1.begin(address1);

  // Bật cảm biến 2
  digitalWrite(pinLox2, HIGH);
  delay(10);

  lox2.begin(address2);
}

void readIrValue() {
  if(analogRead(35) < 2500) {
    IR[0] = 0;
  }
  else {
    IR[0] = 1;
  }
  if(analogRead(34) < 2000) {
    IR[1] = 0;
  }
  else {
    IR[1] = 1;
  }
  if(analogRead(39) < 2500) {
    IR[2] = 0;
  }
  else {
    IR[2] = 1;
  }
  if(analogRead(36) < 2500) {
    IR[3] = 0;
  }
  else {
    IR[3] = 1;
  }
  delayMicroseconds(200);
}

void readLaserValue() {
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  rightLaser = measure1.RangeMilliMeter;
  frontLaser = measure2.RangeMilliMeter;
}


