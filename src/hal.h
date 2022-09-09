void setup();
void print(char *data);
void restore();
void step();
void run();

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
