#define TEMP_SENSOR_PORT 0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int portValue = analogRead(TEMP_SENSOR_PORT);
  float voltaje = 5.0 / 1024 * portValue;
  float temp = voltaje * 100 - 50;
  Serial.print("Temp: ");
  Serial.println(temp);
  delay(1000);
}
