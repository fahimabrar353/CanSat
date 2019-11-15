#define led_pin 13

void bat_setup() {
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

void bat_loop() {
  int sensorValue = analogRead(A0); //read the A0 pin value
  int vol = 10 * (sensorValue * (5.00 / 1023.00) * 2); //convert the value to a true voltage.
  data.Voltage = vol; 
  Serial.print("voltage = ");
  Serial.print(data.Voltage);
  if (data.Voltage < 6.50) //set the voltage considered low battery here
  {
    digitalWrite(led_pin, HIGH);
  }
}
