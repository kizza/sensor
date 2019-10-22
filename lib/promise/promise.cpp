#include "Arduino.h"
#include <functional>
#include "promise.h"

Promise promise() {
  Context context;
  Promise promise = { context };
  return promise;
}

Promise promise(Context context) {
  Promise promise = { context };
  return promise;
}

std::function<Context (Context)> continuation() {
  return [&](Context context) {
    return context;
  };
}

