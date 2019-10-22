#include "Arduino.h"
#include "sensors.h"

void debugMoisture(int value, int percentage) {
  Serial.print("Sensor is ");
  Serial.print(value);
  Serial.print(" or ");
  Serial.print(percentage);
  Serial.println("%");
}

int readMoisture(int sensorPin) {
  int value = analogRead(sensorPin);
  int percentage = constrain(map(value, 1000, 4095, 100, 0), 0, 100);
  debugMoisture(value, percentage);
  return percentage;
}
