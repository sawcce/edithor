#include <stdio.h>

#include "hal.h"
#include "colors.h"

#ifdef _WIN64
#include <conio.h>
#include <windows.h>

HANDLE hStdin, stdOut, screenBuffer;

DWORD cNumRead, fdwMode, i;
INPUT_RECORD irInBuf[128];

DWORD fdwMode, fdwSaveOldMode, cNumRead;

void exitProgram();

void setup() {
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  screenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
                                           FILE_SHARE_WRITE | FILE_SHARE_WRITE,
                                           NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

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

void run() {
  while (1) {
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
        COORD coords = {.X = 0, .Y = 0};

        char *msg = colored(Foreground_Blue, "Hello !");
        WriteConsole(screenBuffer, msg, strlen(msg), NULL, NULL);
        free(msg);
        break;
      default:
        break;
      }
    }
  }
}

void restore() { SetConsoleActiveScreenBuffer(stdOut); }

void print(char * message) {
	WriteConsole(screenBuffer, message, strlen(message), NULL, NULL);
}

void exitProgram(char *message) {
  WriteConsole(stdOut, message, strlen(message), NULL, NULL);
  ExitProcess(1);
}

#endif
