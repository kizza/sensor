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

const int foo = A7;

const int trigPin = 9;
const int echoPin = 10;

void setup() {
  promise()
    .then(initDeepSleep)
    .then(initBoard)
    .then([](Context context) {
      pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
      pinMode(echoPin, INPUT); // Sets the echoPin as an Input
      return context;
    });

    /* .then(initWiFi(WIFI_SSID, WIFI_PASSWORD)) */
    /* .then(flashWith(FlashAsConnected)) */
    /* .then(delayBy(200)) */
    /* .then(initMqtt(mqtt)) */
    /* .then(delayBy(200)) */
    /* .thrown(printError); */
}

void loop()
{
  promise()
    .then(debugLoop)
    .then(debugWith("Beginning work..."))
    .then(turnOnLED)
    .then(measure)
    .then([](Context context) {
      long duration;
      int distance;

      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      Serial.print("Duration was");
      Serial.println(duration);

      // Calculating the distance
      distance= duration*0.034/2;
      // Prints the distance on the Serial Monitor
      Serial.print("Distance: ");
      Serial.println(distance);
      return context;
    })
    .then(turnOffLED)
    .then(delayBy(500));

    /* .then(delayBy(1000)) */
    /* .then(ensureConnected) */
    /* .then([](Context context) { */
    /*   poll(); */
    /*   return context; */
    /* }) */
    /* .then(measure) */
    /* .then(delayBy(1000)) */
    /* .then(turnOffLED) */
    /* // .then(waitForNextLoop) */
    /* .then(goToSleep) */
    /* .thrown([](Context context) { */
    /*   Serial.println("Error within loop..."); */
    /*   Serial.println(context.message); */
    /*   delay(5000); */
    /*   return context; */
    /* }); */
}
