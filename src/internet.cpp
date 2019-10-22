#include "WiFi.h"
#include "internet.h"
#include "promise.h"
#include "env.inc"

Context initWiFi(Context context) {
  delay(10);
  Serial.printf("Connecting to %s..", WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.printf(" connected with %s\n", WiFi.localIP().toString().c_str());
  return context;
}

