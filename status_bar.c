#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "battery_status.h"
#include "time_status.h"
#include "updates_status.h"

#define STATUS_MAX_SIZE 108

Display* dpy;

/* THIS IS THE FORMAT OF THE STATUS BAR STRING AS OF NOW */
/* 

  | 🖴 000% | 🖥️ 000% 🌡️ 00° | ⬇️ 0000 ⬆️ 0000 | 🔔 0000 | FRI 00/00 00:00 | 🔊 000% 

 */
void SetStatus(char* status) {
  XStoreName(dpy, DefaultRootWindow(dpy), status);
  XSync(dpy, 0);
}

void UpdateStatusString(char statusString[STATUS_MAX_SIZE], char* sourceString, int startIndex) {
  for (int i = 0; i < strlen(sourceString); i++) {
    statusString[startIndex + i] = (sourceString)[i];
  }
}

int main() { 
  dpy = XOpenDisplay(NULL);

  /* 19 characters */
  char timeString[20];
  /* 1 spacer */
  /* 3 characters maximum */
  char updatesString[4];
  /* 1 spacer */
  /* 4 characters maximum */
  char batteryString[5];
  
  int counter = 0;

  while(1) {
    /* Update strings if necessary */ 

    SetTimeString(timeString);

    if (counter % 3600 == 0) {
      SetUpdatesString(updatesString);
    }

    if (counter % 10 == 0) { 
      SetBatteryString(batteryString);
    }

    char statusString[STATUS_MAX_SIZE];

    sprintf(statusString, "| 🖴 000% | 🖥️ 000% 🌡️ 00° | ⬇️ 0000 ⬆️ 0000 | 🔔 0000 | FRI 00/00 00:00 | 🔊 000%%");

    SetStatus(statusString);

    counter++;

    sleep(1);
  }

  XCloseDisplay(dpy);
  
  return 0;
} 