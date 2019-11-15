#include "TinyGPS++.h"
#include "SoftwareSerial.h"

SoftwareSerial serial_connection(5, 6); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
void GPS_setup()
{
//  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
 serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
}

void GPSread()
{
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.print("Satellite Count:");
    byte sc=gps.satellites.value();
    data.SCount =sc;
    Serial.println(sc);
    
    Serial.print("Latitude:");
    data.Lat=gps.location.lat();
    Serial.println(data.Lat);
    
    Serial.print("Longitude:");
    data.Longi= gps.location.lng();
    Serial.println(data.Longi);
    
    Serial.println("Speed MPH:");
    data.Speed=gps.speed.mph();
    Serial.println(data.Speed);
    
    Serial.println("Altitude Feet:");
    data.gps_alt =gps.altitude.feet();
    Serial.println(data.gps_alt);
//    Serial.println("");
  }
}
