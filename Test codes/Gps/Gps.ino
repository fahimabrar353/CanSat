#include "TinyGPS++.h"
#include "SoftwareSerial.h"

SoftwareSerial serial_connection(5, 6); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
void setup()
{
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
}

void loop()
{
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.print("Satellite Count:");
    Serial.print(gps.satellites.value());
    Serial.print("  Latitude:");
    Serial.print(gps.location.lat(), 6);
    Serial.print("  Longitude:");
    Serial.print(gps.location.lng(), 6);
    Serial.print("  Speed MPH:");
    Serial.print(gps.speed.mph());
    Serial.print("  Altitude Feet:");
    Serial.print(gps.altitude.feet());
    Serial.print("  Value:");
    uint32_t CurrentTime;
    CurrentTime = gps.time.value(); 
    Serial.print(CurrentTime);

    
    Serial.println("");
  }
}
