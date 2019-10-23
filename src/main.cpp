/*
 * Moisture Sensor
 */

#include "Arduino.h"
#include "env.inc"
#include "promise.h"
#include "internet.h"
#include "mqtt.h"
#include "sensors.h"
#include "pipeline.h"

LEDBurst FlashAsConnected = { new int[5] {0, 0, 0, 1, 1}, 5 };

char* prefixedInteger(char* prefix, int value) {
  char value_str[21]; // enough to hold all numbers up to 64-bits
  sprintf(value_str, "%d", value);
  return strcat(prefix, value_str);
}

Context measure(Context context) {
  int sensorPin = A0;
  char prefix[64] = "Arduino|";
  char* message = prefixedInteger(prefix, readMoisture(sensorPin));
  publish(message);
  return context;
}

MqttConnection mqtt = {
  MQTT_SERVER,
  MQTT_PORT,
  MQTT_USER,
  MQTT_PASSWORD,
  MQTT_SERIAL_PUBLISH_CH,
  MQTT_SERIAL_RECEIVER_CH
};

void setup() {
  promise()
    .then(initBoard)
    .then(initWiFi(WIFI_SSID, WIFI_PASSWORD))
    .then(flashWith(FlashAsConnected))
    .then(delayBy(200))
    .then(initMqtt(mqtt))
    .then(delayBy(200))
    .thrown(printError);
}

void loop()
{
  promise()
    .then(debugLoop)
    .then(debugWith("Beginning work..."))
    .then(turnOnLED)
    .then(delayBy(1000))
    .then(ensureConnected)
    .then([](Context context) {
      poll();
      return context;
    })
    .then(measure)
    .then(delayBy(1000))
    .then(turnOffLED)
    .then(waitForNextLoop)
    .thrown([](Context context) {
      Serial.println("Error within loop...");
      Serial.println(context.message);
      delay(5000);
      return context;
    });
}
