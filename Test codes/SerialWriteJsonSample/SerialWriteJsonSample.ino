#include <ArduinoJson.h>
  // Memory pool for JSON object tree.
  StaticJsonDocument<256> doc;

  // Create the root of the object tree.
  JsonObject root = doc.to<JsonObject>();

  int mission_time = 900;
  int gps_time = 145687;
  String gps_location = "[23.156478, 90.123456]";
//  int gps_location_long = 90.123456;
  int temp = 23;
  double pressure = 58;
  double altitude = 28;
  double battery_voltage = 3.3;
void setup() {
  Serial.begin(9600);
  while (!Serial) continue;

  // Add values in the object
//  root["mission_time"] = serialized(String(mission_time));
//  root["gps_time"] = serialized(String(gps_time));
//  root["gps_location"] = serialized(gps_location);
//  root["temp"] = serialized(String(temp));
//  root["pressure"] = serialized(String(pressure));
//  root["altitude"] = serialized(String(altitude));
//  root["battery_voltage"] = serialized(String(battery_voltage));

//  root.printTo(Serial);
  

}

void loop() {
  mission_time++;
  gps_time++;
  temp+=.01;
  pressure+=.1;
  altitude+=.1;
  battery_voltage-=.1;
  // Memory pool for JSON object tree.
  StaticJsonDocument<256> doc;
  // Create the root of the object tree.
  JsonObject root = doc.to<JsonObject>();
  root["mission_time"] = serialized(String(mission_time));
  root["gps_time"] = serialized(String(gps_time));
  root["gps_location"] = serialized(gps_location);
  root["temp"] = serialized(String(temp));
  root["pressure"] = serialized(String(pressure));
  root["altitude"] = serialized(String(altitude));
  root["battery_voltage"] = serialized(String(battery_voltage));

  serializeJson(root, Serial);
  delay(1000);
}
