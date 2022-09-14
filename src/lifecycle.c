#include "lifecycle.h"

#include "hal.h"

bool shouldRun = true;
Mode currentMode = InsertMode;

void app() {
  setup();

  while (shouldRun) {
    step();
  }

  restore();
}

void handle(InputEvent event) {}

void run() { step(); }
