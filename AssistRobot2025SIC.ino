#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include "Sensor.h"
#include "Algorithm.h"
#include <DabbleESP32.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <Arduino.h>
HardwareSerial SerialPort(2); // Use UART2

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17); 
  Serial.begin(115200);  
  Dabble.begin("ESP32BLE"); // Name of BLE device    
  delay(10);
  pinMode(pinLox1, OUTPUT);
  pinMode(pinLox2, OUTPUT);
  initLaser();
}

void loop() {
  Dabble.processInput();    
  readIrValue();
  readLaserValue();
  char buffer[50];
  sprintf(buffer, "%d %d", rightLaser, frontLaser);
  Terminal.println(buffer);
  delay(100);
}