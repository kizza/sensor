#include "Arduino.h"
#include "board.h"
#include "promise.h"
#include "config.inc"

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 30

RTC_DATA_ATTR int boots = 0;
int loops = 0;

//Function that prints the reason by which ESP32 has been awaken from sleep
void printWakeupReason() {
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case 3  : Serial.println("Wakeup caused by timer"); break;
    case 4  : Serial.println("Wakeup caused by touchpad"); break;
    case 5  : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.println("Wakeup was not caused by deep sleep"); break;
  }
}

Context debugLoop(Context context) {
  Serial.printf("\nBoot %d\n", ++boots);
  printWakeupReason();
  Serial.printf("Loop %d\n", ++loops);
  return context;
}

Context initDeepSleep(Context context) {
  Serial.println("Configuring deep sleep");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  return context;
}

Context goToSleep(Context context) {
  Serial.println("Going to sleep");
  esp_deep_sleep_start();
  return context;
}

Context initBoard(Context context) {
  Serial.begin(115200);
  initLED();
  return context;
}

Context printError(Context error) {
  Serial.print("There was an error: ");
  Serial.println(error.message);
  delay(5000);
  return error;
}

Context waitForNextLoop(Context context) {
  if (TESTING) {
    delay(1000 * 8);
  } else {
    delay(1000 * 60 * 1 * 10);
  }
  return context;
}

std::function<Context (Context)> delayBy(int milliseconds) {
  delay(milliseconds);
  return continuation();
}

std::function<Context (Context)> debugWith(const char* message) {
  Serial.println(message);
  return continuation();
}

std::function<Context (Context)> flashWith(LEDBurst shape) {
  flash(shape);
  return continuation();
}
