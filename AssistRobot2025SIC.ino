#include <DabbleESP32.h>
#include "Sensor.h"

void setup() {
  Serial.begin(115200);              // For debugging
  Dabble.begin("ESP32BLE");  // Name of BLE device
}

void loop() {
  readIRValue();
  Dabble.processInput();          
  char buffer[50];
  sprintf(buffer, "%d %d %d %d", IR[0], IR[1], IR[2], IR[3]);
  Terminal.println(buffer);
}