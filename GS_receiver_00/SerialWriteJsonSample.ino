#include <ArduinoJson.h>

void serial_setup() {

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

void serial_loop() {

  DynamicJsonDocument root(1024);
  root["mission_time"] = serialized("00");

  JsonObject gps  = root.createNestedObject("gps");
  gps["lat"] = data.Lat;
  gps["long"] = data.Long;
  gps["alt"] = data.gps_alt;
  gps["time"] = data.gps_t;
  gps["sat_count"] = data.SCount;
  gps["speed"] = data.Speed;

  root["temp"] = data.temperature;
  root["pressure"] = data.pressure;
  root["altitude"] = data.Alt;
  root["battery_voltage"] = data.Voltage/10.0;
  JsonObject gyro  = root.createNestedObject("gyro");
  gyro["roll"] = data.Roll;
  gyro["pitch"] = data.Pitch;
  gyro["yaw"] = data.Yaw;

  root["soft state"] = data.state;

  serializeJson(root, Serial);
    delay(1000);

}
