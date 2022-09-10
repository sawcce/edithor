#include <stdio.h>

#include "colors.h"
#include "hal.h"

void (*handler)(InputEvent);
unsigned short int termWidth, termHeight = 0;

#ifdef _WIN64
#include <windows.h>

HANDLE hStdin, stdOut, screenBuffer;

DWORD cNumRead, fdwMode, i;
INPUT_RECORD irInBuf[128];

DWORD fdwMode, fdwSaveOldMode, cNumRead;

void exitProgram();

void setup() {
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(stdOut, &csbi);
  termWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  termHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                           FILE_SHARE_WRITE | FILE_SHARE_WRITE,
                                           NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

  SetConsoleMode(screenBuffer, ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS |
                                   ENABLE_VIRTUAL_TERMINAL_PROCESSING);

  if (stdOut == INVALID_HANDLE_VALUE || screenBuffer == INVALID_HANDLE_VALUE) {
    printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    ExitProcess(1);
  }
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  if (!SetConsoleActiveScreenBuffer(screenBuffer)) {
    printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    ExitProcess(1);
  }
}

void step() {
  if (!ReadConsoleInput(hStdin,     // input buffer handle
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

void restore() { SetConsoleActiveScreenBuffer(stdOut); }

void print(char *message) {
  WriteConsole(screenBuffer, message, strlen(message), NULL, NULL);
}

void print_f(char *message) {
  WriteConsole(screenBuffer, message, strlen(message), NULL, NULL);
  free(message);
}

void exitProgram(char *message) {
  WriteConsole(stdOut, message, strlen(message), NULL, NULL);
  ExitProcess(1);
}

#endif
