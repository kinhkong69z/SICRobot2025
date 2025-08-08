#include "Sensor.h"
#include "esp32-hal.h"
#include "esp32-hal-adc.h"


int IR[4];
Adafruit_VL53L0X lox1;
Adafruit_VL53L0X lox2;
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
int rightLaser;
int frontLaser;

void initSerial() {
  HardwareSerial SerialPort(2); // Use UART2
  SerialPort.begin(115200, SERIAL_8N1, 16, 17); 
}

int initLaser() {
  Wire.begin(I2C_SDA, I2C_SCL);
  lox1 = Adafruit_VL53L0X();
  lox2 = Adafruit_VL53L0X();
  delay(10);

  pinMode(pinLox1, OUTPUT);
  pinMode(pinLox2, OUTPUT);

  digitalWrite(pinLox1, LOW);
  digitalWrite(pinLox2, LOW);
  delay(10);
  // Reset pin

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


