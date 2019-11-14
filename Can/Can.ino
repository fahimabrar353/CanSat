/*
  Can - the main cansat controller code
  See readme for project detaitails.
  The circuit:
              See readme section for circuits and connection

  Created 15-11-2019
  By Fahim Abrar @fahimabrar353, Sakib Ahmed @ahmadsum1 
*/




#include "PinConfig.h"
/*

*/

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {

  Serial.begin(9600);

  // Define the radio communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  accelgyro_init();
  GPS_setup();

  mag_setup();

  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  delay(1000);
  BMP_setup();
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

  BMP_loop();

  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);
  processAccelData();
  processGyroData();

  mag_update();
  GPSread();



  // now you should read the gyroscope, accelerometer (and magnetometer if you have it also)
  // NOTE: the gyroscope data have to be in radians
  // if you have them in degree convert them with: DEG_TO_RAD example: gx * DEG_TO_RAD

  deltat = filter.deltatUpdate(); //this have to be done before calling the filter update
  //choose only one of these two:
  //filter.MahonyUpdate(_gx, _gy, _gz, _ax, _ay, _az, deltat);  //mahony is suggested if there isn't the mag and the mcu is slow
  filter.MadgwickUpdate(_gx, _gy, _gz, _ax, _ay, _az, _mx, _my, _mz, deltat);  //else use the magwick, it is slower but more accurate

  pitch = filter.getPitch();
  roll = filter.getRoll();    //you could also use getRollRadians() ecc
  yaw = filter.getYaw();


  Serial.print(roll);
  Serial.print("\t");
  Serial.print(pitch);
  Serial.print("\t");
  Serial.print(yaw);
  Serial.print("\t\t");
  Serial.println(deltat, 6);
  Serial.println();


  // Send the whole data from the structure to the receiver
  radio.write(&data, sizeof(Data_Package));



  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
