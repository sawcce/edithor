#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *colored(Color color, char *message) {
  char *format = "\x1b[%dm%s";

  char *str = malloc(snprintf(NULL, 0, format, color, message));
  sprintf(str, format, color, message);

  return str;
}
