#include "Arduino.h"
#include "board.h"

void initLED() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void flash(int sequence[], int sequenceCount) {
  Serial.print("Flashing ");
  for (int i = 0; i < sequenceCount; i++) {
    Serial.print(sequence[i]);

    if (sequence[i] == 1) {
      delay(200);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(120);
    }
    digitalWrite(LED_BUILTIN, LOW);
    delay(120);
  }
  Serial.println(".");
}

void flash(LEDBurst shape) {
  flash(shape.sequence, shape.length);
}

