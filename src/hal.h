// State functions

// A function to bootstrap the app (setup the buffers, enter raw mode)
void setup();
// Restore the terminal back to it's original state
void restore();
// Runs a step in the app (acquire input and events)
void step();

void print(char *data);

typedef enum { KeyPressed, KeyReleased } InputEventType;

typedef struct {
  char character;
} KeyEvent;

struct InputEvent {
  InputEventType type;
  union {
    KeyEvent keyEvent;
  } event;
};
