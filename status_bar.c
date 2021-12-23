#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "battery_status.h"
#include "time_status.h"
#include "updates_status.h"

#define STATUS_MAX_SIZE 80

Display* dpy;

/* THIS IS THE FORMAT OF THE STATUS BAR STRING AS OF NOW */
/* 

  0-24 DATE
  25 SPACER
  26-28 UPDATES
  29 SPACER
  30-33 BATTERY STATUS

 */
void SetStatus(char* status) {
  XStoreName(dpy, DefaultRootWindow(dpy), status);
  XSync(dpy, 0);
}

void UpdateStatusString(char statusString[STATUS_MAX_SIZE], char** sourceString, int startIndex) {
  for (int i = 0; i < strlen(*sourceString); i++) {
    statusString[startIndex + i] = (*sourceString)[i];
  }
}

int main() {  
  dpy = XOpenDisplay(NULL);

  /* 25 characters */
  char* timeString;
  /* 1 spacer */
  /* 3 characters maximum */
  char* updatesString;
  /* 1 spacer */
  /* 4 characters maximum */
  char* batteryString;
  /* 1 spacer */
  
  int timeCounter = 0;

  char statusString[STATUS_MAX_SIZE] = "";
  for (int i = 0; i < STATUS_MAX_SIZE; i++) {
    statusString[i] = ' ';
  }

  for (;;sleep(1)) {
    SetTimeString(&timeString);
    UpdateStatusString(statusString, &timeString, 0);

    if (timeCounter % 500 == 0) {
      SetUpdatesString(&updatesString);
      UpdateStatusString(statusString, &updatesString, 26);
    }

    if (timeCounter % 10 == 0) { 
      SetBatteryString(&batteryString);
      UpdateStatusString(statusString, &batteryString, 30);
    }

    SetStatus(statusString);

    timeCounter++;
  }

  XCloseDisplay(dpy);
  
  return 0;
} 