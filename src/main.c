#include <conio.h>

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "colors.h"
#include "hal.h"
#include "utils.h"

void rainbow() {
  for (float i = 0; i < 255; i += 255.0 / termWidth) {
    print_f(colored((Color){125, 152, i}, (Color){0, 0, 0}, " "));
  }
  print("\x1b[0m\n");
}

void handle(InputEvent event) {
  switch (event.type) {
  case KeyPressed:
    if (event.event.keyEvent.character == 'r') {
      rainbow();
    } else if (event.event.keyEvent.character == 'c') {
      print("\x1b[2J");
    }
  case KeyReleased:
    // print_f(format("Key '%c' released\n", event.event.keyEvent.character));
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
