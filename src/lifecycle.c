#include "lifecycle.h"

#include "hal.h"
#include <stdio.h>

bool shouldRun = true;
Mode currentMode = InsertMode;

void handle(InputEvent event);
void keyPressed(KeyEvent event);

void app() {
  handler = &handle;
  setup();

  while (shouldRun) {
    step();
  }

  restore();
  printf("Thanks for using Edithor!");
}

void handle(InputEvent event) {
  switch (event.type) {
  case KeyPressed:
    keyPressed(event.event.keyEvent);
    break;
  case KeyReleased:
    break;
  }
}

void keyPressed(KeyEvent event) {
  switch (event.character) {
  case 'q':
    shouldRun = false;
    break;
  }
}

void run() { step(); }
