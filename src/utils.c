#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *format(char *format, ...) {
  va_list formatArgs;
  va_start(formatArgs, format);

  char *output = malloc(snprintf(NULL, 0, format, formatArgs));
  sprintf(output, format, formatArgs);
  return output;
}
