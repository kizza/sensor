#pragma once
#include "Arduino.h"
#define LED_BUILTIN 2

struct LEDBurst {
  int* sequence;
  int length;
};

void initLED();

void flash(int sequence[], int sequenceCount);

void flash(LEDBurst shape);
