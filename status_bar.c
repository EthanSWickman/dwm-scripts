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

#define STATUS_MAX_SIZE 120 

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

  InitCpuTracker();
  InitNetworkTracker();

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
  
  int fiveSecondCounter = 0;
  int oneMinuteCounter = 0;
  int fiveMinuteCounter = 0;

  while(1) {
    sleep(1);
    
    /* every second */
    SetTimeString(timeString);
    SetCpuTempString(cpuTempString);
    SetCpuUsageInt(&cpuUsageInt);
    SetNetworkUpString(networkUpString);
    SetNetworkDownString(networkDownString);
    /* every five seconds */
    if (fiveSecondCounter > 5) {
      SetMemoryUsageInt(&memoryUsageInt);
      fiveSecondCounter = 0;
    }
    /* every minute */
    if (oneMinuteCounter > 60) {
      SetBatteryString(batteryString);
      oneMinuteCounter = 0;
    }
    /* every five minutes */
    if (fiveMinuteCounter > 300) {
      SetUpdatesString(updatesString);
      fiveMinuteCounter = 0;
    }

    char statusString[STATUS_MAX_SIZE];

    char* maxSizeStatus = "| 🖴 000% | 🖥️ 000% 🌡️ 00° | ⬇️ 0000 kb/s ⬆️ 0000 kb/s | 🔔 00000 | Fri 00/00 00:00 | 🔋 100%+";
    printf("%ld is the maximum status size\n", strlen(maxSizeStatus));
    printf("%s\n", maxSizeStatus);
    sprintf(statusString, "| 🖴 %u%% | 🖥️ %u%% 🌡️ %s° | ⬇️ %s ⬆️ %s | 🔔 %s | %s | 🔋 %s", memoryUsageInt, cpuUsageInt, cpuTempString, networkDownString, networkUpString, updatesString, timeString, batteryString);

    SetStatus(statusString);

    fiveSecondCounter++;
    oneMinuteCounter++;
    fiveMinuteCounter++;
  }

  XCloseDisplay(dpy);
  
  return 0;
} 