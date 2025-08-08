#include "Sensor.h"
#include "Algorithm.h"
#include <DabbleESP32.h>

void setup() {
  Serial.begin(115200);  
  initSerial();  
  Dabble.begin("ESP32BLE"); // Name of BLE device    
  while(!initLaser()) {
    Terminal.println("Can't open laser");
  }
}

void loop() {
  readIrValue();
  Dabble.processInput();          
  char buffer[50];
  sprintf(buffer, "%d %d %d %d", IR[0], IR[1], IR[2], IR[3]);
  Terminal.println(buffer);
  readLaserValue();
}