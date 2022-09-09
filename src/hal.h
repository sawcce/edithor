// State function: functions which are the base pillars of the app

// A function to bootstrap the app (setup the buffers, enter raw mode)
void setup();
// Restore the terminal back to it's original state
void restore();
// Runs a step in the app (acquire input and events)
void step();

// Human interaction

// Prints the data to the output
void print(char *data);

typedef enum { KeyPressed, KeyReleased } InputEventType;

typedef struct {
  char character;
} KeyEvent;

typedef struct {
  InputEventType type;
  union {
    KeyEvent keyEvent;
  } event;
} InputEvent;

extern void (*handler)(InputEvent);
