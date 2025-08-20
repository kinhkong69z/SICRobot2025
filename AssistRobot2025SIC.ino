#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include "Sensor.h"
#include "Algorithm.h"
#include <DabbleESP32.h>
#include "mpu.h"
#include "Motor.h"

HardwareSerial SerialPort(2);  // Use UART2

void setup() {
  SerialPort.begin(115200, SERIAL_8N1, 18, 19);
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  Dabble.begin("ESP32BLE");  // Name of BLE device
  delay(10);
  pinMode(pinLox1, OUTPUT);
  pinMode(pinLox2, OUTPUT);
  pinMode(14, OUTPUT);  // Servo pin
  // initLaser();
  // delay(1000);
  calibIR();
  SerialPort.println("#PIDV 1 200 0 60");
  SerialPort.println("#PIDV 2 -200 0 -60");
  SerialPort.println("#SAVE 1");
  SerialPort.println("#SAVE 2");

  // Wake up MPU9250
  writeRegister(MPU9250_ADDR, PWR_MGMT_1, 0x00);
  delay(100);
  // Set gyro full-scale to ±250 dps (00)
  writeRegister(MPU9250_ADDR, GYRO_CONFIG, 0x00);
  SerialPort.println("#PWM 1 200");
  SerialPort.println("#PWM 2 -200");
  calibrateGyro();
  SerialPort.println("#PWM 1 0");
  SerialPort.println("#PWM 2 0");
  lastTime = micros();

  digitalWrite(14, LOW);
  delay(10000);

  testLineFollower();
}

void loop() {
  Dabble.processInput();
  readIrValue();
  // readAngle();
  // readLaserValue();
  // lastTime = micros();
  char buffer[50];
  // sprintf(buffer, "%d %d %d %d %d %d %d", analogRead(36), analogRead(39), analogRead(34), analogRead(35), analogRead(25), analogRead(26), analogRead(27));
  // sprintf(buffer, "%d %d %d %d %d %d %d", irCalib[0], irCalib[1], irCalib[2], irCalib[3], irCalib[4], irCalib[5], irCalib[6]);
  sprintf(buffer, "%d %d %d %d %d %d %d", IR[0], IR[1], IR[2], IR[3], IR[4], IR[5], IR[6]);

  Terminal.println(buffer);
  servo(0);

  // Serial.println(angleZ);
  delay(100);
  // SerialPort.print("#PWM 1 300\n");
  // SerialPort.print("#PWM 2 300\n");
  // Serial.println(buffer);
  // setMotor(300, 300);
}

void testLineFollower() {
  int speed = 250;
  readIrValue();
  while (IR[3] == 0 || IR[6] == 0 ) {
    readIrValue();
    speed = 250;
    if (IR[3] == 1) {
      setMotor(speed, -speed);
    } else if (IR[1] == 1) {
      setMotor(speed - 20, -speed - 20);
    } else if (IR[0] == 1) {
      setMotor(speed - 30, -speed - 30);
    } else if (IR[5] == 1) {
      setMotor(speed + 20, -speed + 20);
    } else if (IR[6] == 1) {
      setMotor(speed + 30, -speed + 30);
    } 
  }
  setMotor(0, 0);
  // SerialPort.println("#PIDV 1 240 0 60");
  // SerialPort.println("#PIDV 2 -230 0 -60");
  // while(IR[0] == 1 && IR[6] == 1)
  // {
  //   setMotor(speed, -speed);
  // }
}

void testServo() {
  for (int i = 0; i < 1000; i++) {
    servo(0);
  }
}
