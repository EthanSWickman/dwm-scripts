#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "time_status.h"

void SetTimeString(char* timeString) {
  time_t rawTime; 
  time(&rawTime);
  struct tm* timeStruct = localtime(&rawTime);
  char parsedTime[19];
  strftime(parsedTime, 20, "%a %b %d %H:%M:%S", timeStruct);
  strcpy(timeString, parsedTime);
}
