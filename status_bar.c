#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "battery_status.h"
#include "time_status.h"
#include "updates_status.h"
#include "cpu_temp_status.h"
#include "cpu_usage_status.h"
#include "memory_usage_status.h"
#include "network_usage_status.h"

#define STATUS_MAX_SIZE 200

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

  DetermineHertz();

  /* 15 characters always */
  char timeString[16];
  /* 5 characters maximum */
  char updatesString[6];
  /* 4 characters maximum */
  char batteryString[5];
  /* 2 characters always */
  char cpuTempString[3];  
  /* 3 characters maximum */
  unsigned int memoryUsageInt;
  /* up to 9 characters */
  char networkUpString[10];
  /* up to 9 characters */
  char networkDownString[10];
  /* up to 3 characters */
  unsigned int cpuUsageInt;
  
  int counter = 0;

  while(1) {
    /* Update strings if necessary */ 

    SetTimeString(timeString);

    SetCpuTempString(cpuTempString);

    SetMemoryUsageInt(&memoryUsageInt);

    SetNetworkUpString(networkUpString);

    SetNetworkDownString(networkDownString);

    SetCpuUsageInt(&cpuUsageInt);

    if (counter % 3600 == 0) {
      SetUpdatesString(updatesString);
    }

    if (counter % 10 == 0) { 
      SetBatteryString(batteryString);
    }

    char statusString[STATUS_MAX_SIZE];

    char* maxSizeStatus = "| 🖴 000% | 🖥️ 000% 🌡️ 00° | ⬇️ 0000 kb/s ⬆️ 0000 kb/s | 🔔 00000 | Fri 00/00 00:00 | 🔋 100%+";
   /*  printf("%ld is the maximum status size\n", strlen(maxSizeStatus));
    printf("%s\n", maxSizeStatus); */
    sprintf(statusString, "| 🖴 %u%% | 🖥️ %u%% 🌡️ %s° | ⬇️ %s ⬆️ %s | 🔔 %s | %s | 🔋 %s", memoryUsageInt, cpuUsageInt, cpuTempString, networkDownString, networkUpString, updatesString, timeString, batteryString);

    SetStatus(statusString);

    counter++;

    sleep(1);
  }

  XCloseDisplay(dpy);
  
  return 0;
} 