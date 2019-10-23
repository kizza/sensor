#include "Arduino.h"
#include "board.h"
#include "promise.h"
#include "config.inc"

int loops = 1;

Context debugLoop(Context context) {
  Serial.printf("\nLoop %d\n", ++loops);
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
