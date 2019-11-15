// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"
//#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
//-------------------------NRF-------------------------------------
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Data_Structs.h"


RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address
// Max size of this struct is 32 bytes - NRF24L01 buffer limit

Data_Package data;
//-------------------------------------------------------------------
MPU6050 accelgyro;
//////////////////////////////////
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_BMP085_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
// Find yours here: http://www.magnetic-declination.com/
// Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
float declinationAngle = 0; //0.22;




////////////////////////////////////////////////////////////////////////////////
//the Serial needs this library https://github.com/geneReeves/ArduinoStreaming

#include "SensorFusion.h"
//#include "Streaming.h"
int16_t gx, gy, gz, ax, ay, az, mx, my, mz;
float _gx, _gy, _gz, _ax, _ay, _az, _mx, _my, _mz;
float pitch, roll, yaw;
float deltat;
SF filter;

#define EULER_DATA
//#define RAW_DATA
//#define PROCESSING


int LED_PIN = LED_BUILTIN ; // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;
