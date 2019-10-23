#include "WiFi.h"
#include "internet.h"
#include "promise.h"

std::function<Context (Context)> initWiFi(const char* ssid, const char* password) {
  delay(10);
  Serial.printf("Connecting to %s..", ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.printf(" connected with %s\n", WiFi.localIP().toString().c_str());

  return continuation();
}
