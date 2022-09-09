#include <conio.h>

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "colors.h"
#include "hal.h"

char *buffer;
char *inputBuffer;

void moveCursorTo(unsigned int x, unsigned int y);

int width, height = 0;

int main() {
  setup();

  while (1) {
    step();
  }

  restore();
  return 0;
}
