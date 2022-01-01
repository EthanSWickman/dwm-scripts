#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "time_status.h"

void SetTimeString(char* timeString) {
  time_t rawTime; 
  time(&rawTime);
  struct tm* timeStruct = localtime(&rawTime);
  char parsedTime[16];
  strftime(parsedTime, 16, "%a %m/%d %H:%M", timeStruct);
  strcpy(timeString, parsedTime);
}
