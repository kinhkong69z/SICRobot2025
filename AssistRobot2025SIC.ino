#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "Sensor.h"
#include "Algorithm.h"
#include <DabbleESP32.h>

HardwareSerial SerialPort(2);  // Use UART2

void setup() {
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  Dabble.begin("ESP32BLE");  // Name of BLE device
  delay(10);
  pinMode(pinLox1, OUTPUT);
  pinMode(pinLox2, OUTPUT);
  // initLaser();
  // delay(1000);
  SerialPort.println("#PIDV 1 200 0 60");
  SerialPort.println("#PIDV 2 -190 0 -60");
  SerialPort.println("#SAVE 1");
  SerialPort.println("#SAVE 2");

  while(true) {
    test();
    if(IR[0] == 1 && IR[1] == 1) break;
  }
}

void loop() {
  // Dabble.processInput();
  readIrValue();
  // readLaserValue();
  char buffer[50];
  sprintf(buffer, "%d %d %d %d %d %d %d", analogRead(35), analogRead(34), analogRead(39), analogRead(36), analogRead(25), analogRead(26), analogRead(27));
  // Terminal.println(buffer);
  // delay(100);
  // SerialPort.print("#PWM 1 300\n");
  // SerialPort.print("#PWM 2 -300\n");
  Serial.println(buffer);
  delay(100);
}
// void test() {
//   int speed_1 = 300;
//   int speed_2 = 300;
//   char buffer[32];
//   while (true) {
//     Dabble.processInput();
//     readIrValue();
//     // readLaserValue();
//     speed_1 = 300;
//     speed_2 = 300;
//     if (IR[0] == 1) SerialPort.println("#PWM 1 500");
//     else if (IR[1] == 1) SerialPort.println("#PWM 1 400");
//     else if (IR[2] == 1) SerialPort.println("#PWM 2 -400");
//     else if (IR[3] == 1) SerialPort.println("#PWM 2 -500");
//     else {
//       SerialPort.println("#PWM 1 300");
//       SerialPort.println("#PWM 2 -300");
//     }

//     // sprintf(buffer, "#PWM 1 %d\n", speed_1);
//     // SerialPort.println("PWM 1 300");

//     // sprintf(buffer, "#PWM 2 %d\n", -speed_2);
//     // SerialPort.print(buffer);
//     delay(10);
//     // sprintf(buffer, "%d %d %d %d", analogRead(35), analogRead(34), analogRead(39), analogRead(36));
//     sprintf(buffer, "%d %d %d %d", IR[0], IR[1], IR[2], IR[3]);
//     Terminal.println(buffer);
//     if (IR[0] == 1 && IR[1] == 1) break;
    
//   }
//   SerialPort.println("#PWM 1 0");
//   SerialPort.println("#PWM 2 0");
// }

void test() {
  readIrValue();
  int speed = 300;
  if (IR[2] == 1) { 
    setMotor(speed, -speed);
  } 
  else if (IR[1] == 1) { 
    setMotor(speed - 50, -speed - 50);
  } 
  else if (IR[0] == 1) { 
    setMotor(speed - 80, -speed - 80);
  } 
  else if (IR[3] == 1) { 
    setMotor(speed + 50, -speed + 50);
  } 
  else if (IR[4] == 1) { 
    setMotor(speed + 80, -speed + 80);
  } 
  else {
    setMotor(0, 0);
  }
}
void setMotor(int left, int right) {
  Serial.print("#VEL 1 "); Serial.println(left);
  Serial.print("#VEL 2 "); Serial.println(right);
}
