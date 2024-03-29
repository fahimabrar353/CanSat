#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  double temperature;
  byte Alt;
  byte X;
  byte Y;
  byte Z;
  byte SCount;
  float Lat;
  float Longi;
  byte Speed;

};
Data_Package data; //Create a variable with the above structure
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
 
}
void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
 
  // Print the data in the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(data.temperature);
  Serial.print("   Altitude: ");
  Serial.print(data.Alt);
  Serial.print("   SatCount: ");
  Serial.print(data.SCount);
  Serial.print("   LAT: ");
  Serial.print(data.Lat);
  Serial.print("   Long: ");
  Serial.println(data.Longi); 
}
}
