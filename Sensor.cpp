#include "esp32-hal.h"
#include "esp32-hal-adc.h"
#include "Sensor.h"
#include "Adafruit_VL53L0X.h"


int IR[4];

int initLaser() {
  Wire.begin(I2C_SDA, I2C_SCL);
  lox1 = Adafruit_VL53L0X();
  lox2 = Adafruit_VL53L0X();
  delay(10);

  digitalWrite(pinLox1, LOW);
  digitalWrite(pinLox2, LOW);
  delay(10);

  digitalWrite(pinLox1, HIGH);
  digitalWrite(pinLox2, HIGH);
  delay(10);

  digitalWrite(pinLox1, HIGH);
  digitalWrite(pinLox2, LOW);

  if(!lox1.begin(address1)) {
    return 0;
  }
  delay(10);

  digitalWrite(pinLox2, HIGH);

  if(!lox2.begin(address2)) {
    return 0;
  }
}

void readIRValue() {
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

void readLaser() {

}


