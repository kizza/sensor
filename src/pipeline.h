#pragma once
#include "Arduino.h"
#include "board.h"
#include "promise.h"

Context initBoard(Context context);

Context printError(Context error);

std::function<Context (Context)> delayBy(int milliseconds);

std::function<Context (Context)> debugWith(const char* message);

std::function<Context (Context)> flashWith(LEDBurst shape);

std::function<Context (Context)> turnOnLED = [](Context context) {
  digitalWrite(LED_BUILTIN, HIGH);
  return context;
};

std::function<Context (Context)> turnOffLED = [](Context context) {
  digitalWrite(LED_BUILTIN, LOW);
  return context;
};
