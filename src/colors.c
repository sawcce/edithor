#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *colored(Color bg, Color fg, char *message) {
  char *format = "\x1b[48;2;%i;%i;%im\x1b[38;2;%i;%i;%im%s\x1b[0m";

  char *str = malloc(
      snprintf(NULL, 0, format, bg.r, bg.g, bg.b, fg.r, fg.g, fg.b, message));
  sprintf(str, format, bg.r, bg.g, bg.b, fg.r, fg.g, fg.b, message);

  return str;
}
