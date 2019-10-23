#pragma once
#include "promise.h"

std::function<Context (Context)> initWiFi(const char* ssid, const char* password);
