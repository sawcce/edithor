#include <stdbool.h>

typedef enum {
  InsertMode,
  NavigateMode,
} Mode;

extern bool shouldRun;
extern Mode currentMode;

void app();
