#include <PubSubClient.h>
#include "WiFi.h"
#include "board.h"
#include "promise.h"
#include "mqtt.h"

extern bool TESTING;

WiFiClient wifiClient;
PubSubClient client(wifiClient);
LEDBurst FlashAsBeep = { new int[3] {0, 0, 0}, 3 };

void poll() {
  client.loop();
}

MqttConnection connection;

void mqttCallback(char* topic, byte *payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("channel:");
  Serial.println(topic);
  Serial.print("data:");
  Serial.write(payload, length);
  Serial.println();
}

void reconnect() {
  if (!client.connected()) {
    Serial.print("Connecting to MQTT..");
  }
  while (!client.connected()) {
    Serial.print(".");

    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str(), connection.user, connection.password)) {
      Serial.println(" connected");
      flash(FlashAsBeep);
      client.publish("awake", "hello world");
      // client.subscribe(connection.listenChannel);
    } else {
      Serial.print(" failed, error=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void publish(char *message){
  if (TESTING) {
    Serial.printf("Debug: %s\n", message);
  } else {
    Serial.printf("Publishing %s\n", message);
    client.publish(connection.publishChannel, message);
  }
}

std::function<Context (Context)> initMqtt(MqttConnection Connection) {
  connection = Connection;
  client.setServer(connection.server, connection.port);
  client.setCallback(mqttCallback);
  reconnect();
  return continuation();
}

Context ensureConnected(Context context) {
  if (!client.connected())
  {
    Serial.println("MQTT disconnected");
    reconnect();
  }

  return context;
}
