#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "cpu_usage_status.h"

/* read /proc/stat over a certain amount of time and detect the change in idle time vs active time to get the CURRENT usage percentage */
long int clockHertz; 
long int numCpus;

unsigned long long prevDowntime;

void InitCpuTracker() {
  FILE* openFile = fopen("/proc/stat", "r");

  fscanf(openFile, "%*s %*llu %*llu %*llu %llu", &prevDowntime);

  fclose(openFile);

  clockHertz = sysconf(_SC_CLK_TCK);
  numCpus = sysconf(_SC_NPROCESSORS_ONLN);
}

void SetCpuUsageInt(unsigned int* cpuUsageInt) {
  FILE* openFile = fopen("/proc/stat", "r"); 

  unsigned long long currDownTime;
 
  fscanf(openFile, "%*s %*llu %*llu %*llu %llu", &currDownTime);

  unsigned int usagePercent = 100 - (unsigned int) (currDownTime - prevDowntime) / (unsigned int) (clockHertz * numCpus / 100);

  prevDowntime = currDownTime;

  *cpuUsageInt = usagePercent;
}