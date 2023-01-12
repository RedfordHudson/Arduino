// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

double ang_x,ang_y,ang_z;
int16_t accel_x, accel_y, accel_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t gyro_offset_x, gyro_offset_y, gyro_offset_z;
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  quantifyOffsets(30);
}

void quantifyOffsets(int iterations) {
  gyro_offset_x = 0;
  gyro_offset_y = 0;
  gyro_offset_z = 0;

  for (unsigned int i = 0; i < iterations; i++) {
    beginTransmission();
    retrieveValues();

    gyro_offset_x += gyro_x;
    gyro_offset_y += gyro_y;
    gyro_offset_z += gyro_z;
  }
  gyro_offset_x /= iterations;
  gyro_offset_y /= iterations;
  gyro_offset_z /= iterations;
}

void loop() {
  beginTransmission();
  retrieveValues();
  accelToTilt();
  writeValues();
}

void beginTransmission() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
}

void retrieveValues() {
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accel_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accel_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accel_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
}

void accelToTilt() {
  ang_x = atan2(accel_y, accel_z)+PI;
  ang_y = atan2(accel_x, accel_z)+PI;
  ang_z = atan2(accel_y, accel_x)+PI;
}

double scale = 2^15;

void writeValue(double value) {
  Serial.print(String(value) + " ");
  // Serial.print(convert_int16_to_str(value));
  // Serial.print(String(value/range ? scale : sin(value)) + " ");
}

void writeValues() {
  writeValue(ang_x);
  writeValue(ang_y);
  writeValue(ang_z);

  writeValue(accel_x);
  writeValue(accel_y);
  writeValue(accel_z - 15000);

  // writeValue(gyro_x);
  // writeValue(gyro_y);
  // writeValue(gyro_z);

  writeValue(gyro_x - gyro_offset_x);
  writeValue(gyro_y - gyro_offset_y);
  writeValue(gyro_z - gyro_offset_z);
  
  // Serial.print(temperature/340.00+36.53);
  Serial.println();
}