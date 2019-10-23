#pragma once
#include "promise.h"

struct MqttConnection {
    const char* server;
    int port;
    const char* user;
    const char* password;
    const char* publishChannel;
    const char* listenChannel;
};

void poll();

void mqttCallback(char* topic, byte *payload, unsigned int length);

void reconnect();

void publish(char *message);

std::function<Context (Context)> initMqtt(MqttConnection connection);

Context ensureConnected(Context context);
