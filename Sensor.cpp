#include "Sensor.h"
#include "esp32-hal.h"
#include "esp32-hal-adc.h"


int IR[7];
int irCalib[7] = {0, 0, 0, 0, 0, 0, 0};

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

void calibIR() {
  for(int i = 0; i < 1000; i++) {
    irCalib[0] += analogRead(36);
    irCalib[1] += analogRead(39);
    irCalib[2] += analogRead(34);
    irCalib[3] += analogRead(35);
    irCalib[4] += analogRead(25);
    irCalib[5] += analogRead(26);
    irCalib[6] += analogRead(27);
  }
  irCalib[0] = irCalib[0] / 1000 + 800;
  irCalib[1] = irCalib[1] / 1000 + 1000;
  irCalib[2] = irCalib[2] / 1000 + 1000;
  irCalib[3] = irCalib[3] / 1000 + 1000;
  irCalib[4] = irCalib[4] / 1000 + 1000;
  irCalib[5] = irCalib[5] / 1000 + 1000;
  irCalib[6] = irCalib[6] / 1000 + 1000;
}

void readIrValue() {
  if(analogRead(36) < irCalib[0]) {
    IR[0] = 0;
  }
  else {
    IR[0] = 1;
  }
  if(analogRead(39) < irCalib[1]) {
    IR[1] = 0;
  }
  else {
    IR[1] = 1;
  }
  if(analogRead(34) < irCalib[2]) {
    IR[2] = 0;
  }
  else {
    IR[2] = 1;
  }
  if(analogRead(35) < irCalib[3]) {
    IR[3] = 0;
  }
  else {
    IR[3] = 1;
  }
  if(analogRead(25) < irCalib[4]) {
    IR[4] = 0;
  }
  else {
    IR[4] = 1;
  }
  if(analogRead(26) < irCalib[5]) {
    IR[5] = 0;
  }
  else {
    IR[5] = 1;
  }
  if(analogRead(27) < irCalib[6]) {
    IR[6] = 0;
  }
  else {
    IR[6] = 1;
  }
  delayMicroseconds(200);
  
}

void readLaserValue() {
  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);
  rightLaser = measure1.RangeMilliMeter;
  frontLaser = measure2.RangeMilliMeter;
}

void servo(int angle) {
  int pulse = (1000 * 1.0 * angle / 180) + 1500;
  digitalWrite(14, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(14, LOW);
  pulse = 19999 - pulse;
  delayMicroseconds(pulse);
  Serial.println(pulse);
}


