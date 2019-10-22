#pragma once
#include "Arduino.h"
#include <functional>

struct Context {
  const char* message;
  bool errored;

  Context(): message(""), errored(false) {};

  Context error(const char* message) {
    Context context;
    context.message = message;
    context.errored = true;
    return context;
  }
};

struct Promise {
  Context context;

  Promise then(std::function<Context (Context)> lambda) {
    if (context.errored) {
      Serial.println("Skipping due to error");
      return Promise { context };
    }

    Context next = lambda(context);
    return Promise { next };
  }

  Promise thrown(std::function<Context (Context)> lambda) {
    if (context.errored) {
      Context rejected = lambda(context);
      rejected.errored = false; // once caught, continue passing down un-errored
      return Promise { rejected };
    } else {
      return Promise { context };
    }
  }

  Promise(Context init) : context(init) { }
};

Promise promise();

Promise promise(Context context);

std::function<Context (Context)> continuation();
