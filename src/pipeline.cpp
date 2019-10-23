#include "Arduino.h"
#include "board.h"
#include "promise.h"

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
