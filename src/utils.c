#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *format(char *format, ...) {
  va_list formatArgs;
  va_start(formatArgs, format);

  int len = snprintf(NULL, 0, format, formatArgs);

  char *output = malloc(len);
  vsprintf_s(output, len + 1, format, formatArgs);
  return output;
}
