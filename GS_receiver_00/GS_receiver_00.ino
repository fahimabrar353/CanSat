#include <SPI.h>
//https://github.com/nRF24/RF24 v1.3.3
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
#include "Data_Structs.h"

Data_Package data; //Create a variable with the above structure
void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver

  serial_setup();

}
void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure

    // Print the data in the Serial Monitor
    //  Serial.print("Temperature: ");
    //  Serial.print(data.temperature);
    //  Serial.print("   Altitude: ");
    //  Serial.print(data.Alt);
    //  Serial.print("   SatCount: ");
    //  Serial.print(data.SCount);
    //  Serial.print("   LAT: ");
    //  Serial.print(data.Lat);
    //  Serial.print("   Long: ");
    //  Serial.println(data.Longi);
    //      Serial.print("   Battery: ");
    //      Serial.println(data.Voltage);


    serial_loop();
//    Serial.println(data.Voltage);
  }
}
