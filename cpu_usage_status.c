#include <stdio.h>
#include <string.h>

#include "cpu_usage_status.h"

/* read /proc/stat over a certain amount of time and detect the change in idle time vs active time to get the CURRENT usage percentage */

void SetCpuUsageString(char* cpuUsageString) {
  char cpuUsage[4];

  strcpy(cpuUsageString, cpuUsage);
}