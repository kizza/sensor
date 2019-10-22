#pragma once
#include "promise.h"

void poll();

void mqttCallback(char* topic, byte *payload, unsigned int length);

void reconnect();

void publish(char *message);

Context initMqtt(Context context);

Context ensureConnected(Context context);
