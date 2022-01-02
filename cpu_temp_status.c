#include <stdio.h>
#include <string.h>

#include "cpu_temp_status.h"

void SetCpuTempString(char* cpuTempString) {
  FILE* openFile = fopen("/sys/bus/acpi/devices/LNXTHERM:00/thermal_zone/temp", "r");

  char temp[3];

  fgets(temp, 3, openFile);

  fclose(openFile);

  strcpy(cpuTempString, temp);
}
