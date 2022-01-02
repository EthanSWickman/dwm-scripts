#include <stdio.h>
#include <string.h>

#include "memory_usage_status.h"

void SetMemoryUsageInt(unsigned int* memoryUsagePercent) {
  FILE* openFile = fopen("/proc/meminfo", "r");

  unsigned int memAvailable;
  unsigned int memTotal;

  fscanf(openFile, "%*s %u %*s\n%*s %*u %*s\n%*s %u", &memTotal, &memAvailable);  

  fclose(openFile);

  unsigned int memPercentInt = 100 - (memAvailable * 100)/memTotal;

  *memoryUsagePercent = memPercentInt;
}