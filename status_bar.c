#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "battery_status.h"
#include "time_status.h"
#include "updates_status.h"
#include "cpu_temp_status.h"

#define STATUS_MAX_SIZE 121

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

  /* 15 characters always */
  char timeString[16];
  /* 5 characters maximum */
  char updatesString[6];
  /* 4 characters maximum */
  char batteryString[5];
  /* 2 characters always */
  char cpuTempString[3];  

  int counter = 0;

  while(1) {
    /* Update strings if necessary */ 

    SetTimeString(timeString);

    SetCpuTempString(cpuTempString);

    if (counter % 3600 == 0) {
      SetUpdatesString(updatesString);
    }

    if (counter % 10 == 0) { 
      SetBatteryString(batteryString);
    }

    char statusString[STATUS_MAX_SIZE];

    char* maxSizeStatus = "| 🖴 000% | 🖥️ 000% 🌡️ 00° | ⬇️ 0000 ⬆️ 0000 | 🔔 00000 | Fri 00/00 00:00 | 🔊 000% | 🔋 100%+";
   /*  printf("%ld is the maximum status size\n", strlen(maxSizeStatus));
    printf("%s\n", maxSizeStatus); */
    /* memory, cpu use/temp, down/up, package upgrades, date/time, volume */
    sprintf(statusString, "| 🖴 000%% | 🖥️ 000%% 🌡️ %s° | ⬇️ 0000 ⬆️ 0000 | 🔔 %s | %s | 🔊 000%% | 🔋 %s", cpuTempString, updatesString, timeString, batteryString);

    SetStatus(statusString);

    counter++;

    sleep(1);
  }

  XCloseDisplay(dpy);
  
  return 0;
} 