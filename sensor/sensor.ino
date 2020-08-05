#include <TM1637Display.h>

#define DISPLAY_DIO_PORT 9
#define DISPLAY_CLK_PORT 8
#define TEMP_SENSOR_PORT 0

#define DEGREES_SEGMENTS 0b01100011
#define MINUS_SEGMENTS 0b01000000

TM1637Display display(DISPLAY_CLK_PORT, DISPLAY_DIO_PORT);

float readTemp() {
  int portValue = analogRead(TEMP_SENSOR_PORT);
  Serial.print("Port: ");
  Serial.print(portValue);
  float voltage = (portValue * 5.0) / 1024;
  Serial.print(" ");
  Serial.print("Volt: ");
  Serial.print(voltage);
  float temp = voltage * 100 - 50;
  Serial.print(" ");
  Serial.print("Temp: ");
  Serial.println(temp);
  return temp;
}

void showTemp(float temp) {
  uint8_t segments[] = { 0x00, 0x00, 0x00, 0x00 };
  if (temp < 0) {
    segments[0] = MINUS_SEGMENTS;
  }
  segments[1] = display.encodeDigit((int)temp / 10);
  segments[2] = display.encodeDigit((int)temp % 10);
  segments[3] = DEGREES_SEGMENTS;
  display.setSegments(segments);
}

void setup() {
  Serial.begin(9600);
  display.setBrightness(7, true);
}

void loop() {
  float temp = readTemp();
  showTemp(temp);
  delay(1000);
}
