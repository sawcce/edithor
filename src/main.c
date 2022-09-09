#include <conio.h>

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "colors.h"
#include "hal.h"
#include "utils.h"

char *buffer;
char *inputBuffer;

void moveCursorTo(unsigned int x, unsigned int y);

int width, height = 0;

void handle(InputEvent event) {
  switch (event.type) {
  case KeyPressed:
    print_f(format("Key '%s' pressed\n", event.event.keyEvent.character));
  case KeyReleased:
    print_f(format("Key '%s' released\n", event.event.keyEvent.character));
    break;
  }
}

int main() {
  setup();
  handler = &handle;

  while (1) {
    step();
  }

  restore();
  return 0;
}
