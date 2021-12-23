#include <stdio.h>
#include <string.h>

#include "battery_status.h"

void SetBatteryString(char** batteryString) {
  /* FILE* openFile = fopen("/sys/class/power_supply/BAT0/capacity","r");
  
  char* battPercentage;

  fgets(battPercentage, 3, openFile);

  fclose(openFile);

  while (strlen(battPercentage) < 3) {
    battPercentage = strcat(" ", battPercentage);
  }

  openFile = fopen("/sys/class/power_supply/BAT0/status", "r");

  int battStatus = fgetc(openFile);

  if (battStatus = 'C') {
    *batteryString = strcat(battPercentage, "+");
  }
  else if (battStatus = 'D') {
    *batteryString = strcat(battPercentage, "-");
  }
  else {
    *batteryString = strcat(battPercentage, "*");
  }
  
  fclose(openFile); */

  // *batteryString = "100+";
} 