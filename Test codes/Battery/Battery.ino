#define led_pin 13

void bat_setup() {
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
}

void bat_loop() {
  int sensorValue = analogRead(A0); //read the A0 pin value
  float voltage = sensorValue * (5.00 / 1023.00) * 2; //convert the value to a true voltage.
  Serial.print("voltage = ");
  Serial.print(voltage);
  if (voltage < 6.50) //set the voltage considered low battery here
  {
    digitalWrite(led_pin, HIGH);
  }
}
