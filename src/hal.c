#include <stdio.h>
#include <string.h>

#include "colors.h"
#include "hal.h"

void (*handler)(InputEvent);
unsigned short int termWidth, termHeight = 0;

#ifdef _WIN64
#include <windows.h>

HANDLE stdIn, stdOut;

DWORD cNumRead, fdwMode, i;
INPUT_RECORD irInBuf[128];

DWORD fdwMode, fdwSaveOldMode, cNumRead;

void exitProgram();

void setup() {
  stdIn = GetStdHandle(STD_INPUT_HANDLE);
  stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  if (!GetConsoleMode(stdIn, &fdwSaveOldMode))
    exitProgram("Couldn't get console mode!");

  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(stdOut, &csbi);
  termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  termHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  SetConsoleMode(stdIn, ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS |
                            ENABLE_VIRTUAL_TERMINAL_PROCESSING);

  // Alternate Screen Buffer sequence
  // https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#alternate-screenBufferscreen-buffer
  print("\x1b[?1049h");
}

void step() {
  if (!ReadConsoleInput(stdIn,      // input buffer handle
                        irInBuf,    // buffer to read into
                        128,        // size of read buffer
                        &cNumRead)) // number of records read
    exitProgram("ReadConsoleInput");
  for (int i = 0; i < cNumRead; i++) {
    INPUT_RECORD event = irInBuf[i];

    switch (event.EventType) {
    case KEY_EVENT:
      if (event.Event.KeyEvent.uChar.UnicodeChar == 'q') {
        exitProgram("Cya!");
      }

      InputEvent eventToHandle;
      eventToHandle.type =
          (event.Event.KeyEvent.bKeyDown) ? KeyPressed : KeyReleased;
      eventToHandle.event.keyEvent.character =
          event.Event.KeyEvent.uChar.UnicodeChar;

      handler(eventToHandle);
      break;
    case WINDOW_BUFFER_SIZE_EVENT:
      termWidth = event.Event.WindowBufferSizeEvent.dwSize.X;
      termHeight = event.Event.WindowBufferSizeEvent.dwSize.Y;
    default:
      break;
    }
  }
}

void restore() {
  SetConsoleMode(stdIn, fdwSaveOldMode);

  // Alternate Screen Buffer sequence
  // https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#alternate-screenBufferscreen-buffer
  print("\x1b[?1049l");
}

void print(char *message) {
  WriteConsole(stdOut, message, strlen(message), NULL, NULL);
}

void print_f(char *message) {
  WriteConsole(stdOut, message, strlen(message), NULL, NULL);
  free(message);
}

void exitProgram(char *message) {
  print(message);
  print("\n");
  ExitProcess(1);
}

#endif
